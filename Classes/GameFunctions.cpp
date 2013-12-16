#include "GameFunctions.h"

float GameFunctions::getTimeTick() 
{
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (float) millisecs;
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
	return rand() % (int)high + (int)low;
}

//I believe this can return a number between low and (high - 1), inclusive
int GameFunctions::randomValueBetween(int low , int high) 
{
	return rand() % (int)high + (int)low;
}