#include "GameFunctions.h"
#include <sstream>
#include <string>

unsigned long long GameFunctions::getTimeTick()
{
	//timeval time;
	//gettimeofday(&time, NULL);
	//unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	//return (float) millisecs;
    
    //http://stackoverflow.com/questions/16177295/get-time-since-epoch-in-milliseconds-preferably-using-c11-chrono
    unsigned long long milliseconds_since_epoch =
    std::chrono::system_clock::now().time_since_epoch() /
    std::chrono::milliseconds(1);
    
    return milliseconds_since_epoch;
}

//I implemented my own just because I am not sure about cross-platform compatibility of c libraries (cmath)
int GameFunctions::getAbsoluteValue(int num)
{
	if (num < 0)
		return num * (-1);
	else
		return num;
}

//I believe this can return a number between low and (high - 1), inclusive
float GameFunctions::randomValueBetween(float low , float high) 
{
	//http://stackoverflow.com/questions/686353/c-random-float-number-generation
	return low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low)));
}

//I believe this can return a number between low and (high - 1), inclusive
int GameFunctions::randomValueBetween(int low , int high) 
{
	return rand() % ((high - low) + 1) + low;
}

//the NDK compiler does not support std::to_string, so this is a workaround
//http://stackoverflow.com/questions/22774009/android-ndk-stdto-string-support
//template <typename T>
//this was generic but it was causing compilation problems.
std::string GameFunctions::to_string(int value)
{
	std::ostringstream os;
    os << value;
    return os.str();
}