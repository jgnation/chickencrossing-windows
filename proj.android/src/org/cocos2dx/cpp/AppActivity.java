/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.annotation.TargetApi;
import android.app.Activity;
import android.graphics.Color;
import android.graphics.Point;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.View;
import android.view.WindowManager;
import android.widget.LinearLayout;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;
import com.sbstrm.appirater.Appirater;

public class AppActivity extends Cocos2dxActivity {
	private AdView adView;
	private static final String AD_UNIT_ID_BANNER = "ca-app-pub-8133410011148346/2441787914";
	private static final String AD_UNIT_ID_INTERSTITIAL = "ca-app-pub-8133410011148346/9374468716";	
	private static AppActivity _appActivity;
	private static InterstitialAd interstitial;
	private static IabHelper mHelper;
	private static IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener;
	private static IabHelper.QueryInventoryFinishedListener mGotInventoryListener;
	private boolean isPremium;
	private static String SKU_PREMIUM = "blah";
	private static Activity thisActivity;

    @Override
	protected void onCreate(Bundle savedInstanceState){
    	super.onCreate(savedInstanceState);
    	thisActivity = this;
    	
    	isPremium = false;
    	isPremium();
    	
    	//TODO: check out sample project for tips on how to compute/hide this value rather than store it literally
    	String base64EncodedPublicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAqi7eaTzatZp2aUpbzH8LN3R6R1HeVkap4NyPguST0JuBHZCIBWx0Z/IWy8XgP1ikL+Hrz9by+xXp+TUqrtpRD49hII5LASZ1fBiTu3qh12QvjuJjEMTYFBdVVH/2UXGHNA18Ei6lAbx8yJBEDhGPeyNqPetnArJwJb+D/79MRdUtOHRBqH6kkJe3stHlykyhmwpi8ZcTEVw1wzbuBGNSqCEDd0fmJ79w7jZYY7DT3/6YpRPaOe2p+/FezPrUlKDI9o/y9uKEtXivotoy3KukryeTlHIoMLJEdgnTbDGZckK41DRlpUpH0qkG/tiDPqEkcalSbKJhqbctroJm6QF7yQIDAQAB";
    	mHelper = new IabHelper(this, base64EncodedPublicKey);
    	mHelper.startSetup(new IabHelper.OnIabSetupFinishedListener() {
    		public void onIabSetupFinished(IabResult result) {
    			if (!result.isSuccess()) {
    				// Oh noes, there was a problem.
    				Log.d(TAG, "Problem setting up In-app Billing: " + result);
    			}
    			Log.d(TAG, "In-app Billing successfully set up.");
    			// Hooray, IAB is fully set up!
			}
		});
    	
    	mPurchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {
    		public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
    			if (result.isFailure()) {
    				Log.d(TAG, "Error purchasing: " + result);
    				return;
    			} else if (purchase.getSku().equals(SKU_PREMIUM)) {
    				makePurchaseCallback(true);
    			}
    		}
    	};
    	
		mGotInventoryListener = new IabHelper.QueryInventoryFinishedListener() {
			public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
				if (result.isFailure()) {
					// handle error here
				}
				else {
					// does the user have the premium upgrade?
					isPremium = inventory.hasPurchase(SKU_PREMIUM);        
					// update UI accordingly
				}
			}
    	};
    	
    	setupBannerAd();
        setupInterstitial();
        Appirater.appLaunched(this);
        
        _appActivity = this;
    }
    
    private void setupBannerAd() {
    	getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

    	int width = getDisplaySize(getWindowManager().getDefaultDisplay()).x;

		LinearLayout.LayoutParams adParams = new LinearLayout.LayoutParams(
				width, LinearLayout.LayoutParams.WRAP_CONTENT);

		adView = new AdView(this);
		adView.setAdSize(AdSize.SMART_BANNER);
		adView.setAdUnitId(AD_UNIT_ID_BANNER);

		AdRequest adRequest = new AdRequest.Builder()
			.addTestDevice("74CF565D181FBE42D5B6C217467E561F")
			.build();

		adView.loadAd(adRequest);
        adView.setBackgroundColor(Color.BLACK);
        adView.setBackgroundColor(0);
        addContentView(adView,adParams);
    }
    
    private void setupInterstitial() {
    	interstitial = new InterstitialAd(this);
        interstitial.setAdUnitId(AD_UNIT_ID_INTERSTITIAL);
        
        AdRequest adRequest = new AdRequest.Builder()
    		.addTestDevice("74CF565D181FBE42D5B6C217467E561F")
    		.build();
        
        interstitial.setAdListener(new AdListener() {
        	//TODO: sometimes these loadAd call fails. why?
        	
        	@Override
        	public void onAdFailedToLoad(int errorCode) {
        		AdRequest adRequest = new AdRequest.Builder()
        			.addTestDevice("74CF565D181FBE42D5B6C217467E561F")
        			.build();
        		interstitial.loadAd(adRequest);
        	}
        	
        	@Override
        	public void onAdClosed() {
        		AdRequest adRequest = new AdRequest.Builder()
    				.addTestDevice("74CF565D181FBE42D5B6C217467E561F")
    				.build();
        		interstitial.loadAd(adRequest);
        	}
        });
        
        interstitial.loadAd(adRequest);
    }
    
    public static void showInterstitial() {
		_appActivity.runOnUiThread(new Runnable() {
		    @Override
		    public void run() {
		    	if (interstitial.isLoaded()) {
                    interstitial.show();
                }
		    }
		});
    }

    public static void hideAd() {
    	_appActivity.runOnUiThread(new Runnable() {
    		@Override
    		public void run() {
    			if (_appActivity.adView.isEnabled())
    				_appActivity.adView.setEnabled(false);
    			if (_appActivity.adView.getVisibility() != 4 )
    				_appActivity.adView.setVisibility(View.INVISIBLE);
    		}
    	});
    }

    public static void showAd() {
    	_appActivity.runOnUiThread(new Runnable() {
    		@Override
    		public void run() {	
    			if (!_appActivity.adView.isEnabled())
    				_appActivity.adView.setEnabled(true);
    			if (_appActivity.adView.getVisibility() == 4 )
    				_appActivity.adView.setVisibility(View.VISIBLE);	
    		}
    	});
    }
    
    //maybe this shouldn't be static?
    public static void makePurchase() {
    	//call must be made on main thread
    	mHelper.launchPurchaseFlow(thisActivity, SKU_PREMIUM, 10001, mPurchaseFinishedListener, "bGoa+V7g/yqDXvKRqq+JTFn4uQZbPiQJo4pf9RzJ");
    }
    public static native void makePurchaseCallback(boolean isSuccessful);
    
    public static void isPremium() {
    	mHelper.queryInventoryAsync(mGotInventoryListener);
    }    
    public static native void isPremiumCallback(boolean isPremium);

	@Override
	protected void onResume() {
		super.onResume();
		if (adView != null) {
			adView.resume();
		}
	}

	@Override
	protected void onPause() {
		if (adView != null) {
			adView.pause();
		}
		super.onPause();
	}

    @Override
    protected void onDestroy() {
    	adView.destroy();
    	
    	if (mHelper != null) {
    		mHelper.dispose();
    	}
    	mHelper = null;

        super.onDestroy();
    }
    
    // Helper get display screen to avoid deprecated function use
 	private Point getDisplaySize(Display d) {
         if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
             return getDisplaySizeGE11(d);
         }
         return getDisplaySizeLT11(d);
     }

     @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
     private Point getDisplaySizeGE11(Display d) {
         Point p = new Point(0, 0);
         d.getSize(p);
         return p;
     }
     
     private Point getDisplaySizeLT11(Display d) {
         try {
             Method getWidth = Display.class.getMethod("getWidth", new Class[] {});
             Method getHeight = Display.class.getMethod("getHeight", new Class[] {});
             return new Point(((Integer) getWidth.invoke(d, (Object[]) null)).intValue(), ((Integer) getHeight.invoke(d, (Object[]) null)).intValue());
         }
         catch (NoSuchMethodException e2) { // None of these exceptions should ever occur. 
             return new Point(-1, -1);
         }
         catch (IllegalArgumentException e2) {
             return new Point(-2, -2);
         }
         catch (IllegalAccessException e2) {
             return new Point(-3, -3);
         }
         catch (InvocationTargetException e2) {
             return new Point(-4, -4);
         }
     }
	
	//this was overriden to fix the ClippingNode creating a white screen
	//http://discuss.cocos2d-x.org/t/clippingnode-to-mask/15953/4
	//https://github.com/cocos2d/cocos2d-js/commit/da18d27379330ff9a150f7c79674aa0a3e3a4a54
	@Override
	public Cocos2dxGLSurfaceView onCreateView() {
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
		return glSurfaceView;
	}
}
