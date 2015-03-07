LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
					../../Classes/AcceleratingLane.cpp \
                   ../../Classes/AdmobHelper.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/Background.cpp \
				   ../../Classes/Bus.cpp \
				   ../../Classes/Car.cpp \
				   ../../Classes/Chicken.cpp \
				   ../../Classes/Dimensions.cpp \
				   ../../Classes/DisappearingLog.cpp \
				   ../../Classes/Egg.cpp \
				   ../../Classes/EggScrambleLevel.cpp \
				   ../../Classes/EggScrambleLevelFactory.cpp \
				   ../../Classes/EggScrambleModeLayer.cpp \
				   ../../Classes/GameFunctions.cpp \
				   ../../Classes/GameLayer.cpp \
				   ../../Classes/GameOverLayer.cpp \
				   ../../Classes/HUDLayer.cpp \
				   ../../Classes/Lane.cpp \
				   ../../Classes/Level.cpp \
				   ../../Classes/LevelFactory.cpp \
				   ../../Classes/LevelManager.cpp \
				   ../../Classes/LevelSelectLayer.cpp \
				   ../../Classes/Log.cpp \
				   ../../Classes/MainModeLayer.cpp \
				   ../../Classes/MainModeLevel.cpp \
				   ../../Classes/MainModeLevelFactory.cpp \
				   ../../Classes/MenuAboutLayer.cpp \
				   ../../Classes/MenuButtonLayer.cpp \
				   ../../Classes/MenuInstructionsLayer.cpp \
				   ../../Classes/MenuLayer.cpp \
				   ../../Classes/MenuStoreLayer.cpp \
				   ../../Classes/PauseLayer.cpp \
				   ../../Classes/PurchaseCallback.cpp \
				   ../../Classes/PurchaseCallbackHelper.cpp \
				   ../../Classes/PurchaseCallbackIOS.cpp \
				   ../../Classes/PurchaseHelper.cpp \
				   ../../Classes/SpriteContainer.cpp \
				   ../../Classes/TopScore.cpp \
				   ../../Classes/Truck.cpp \
				   ../../Classes/Vehicle.cpp \
				   ../../Classes/VehicleFactory.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
