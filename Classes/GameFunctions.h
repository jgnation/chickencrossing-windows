#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "cocos2d.h"
#include <string>
using namespace cocos2d;

namespace GameFunctions
{
	unsigned long long getTimeTick();

	//I implemented my own just because I am not sure about cross-platform compatibility of c libraries (cmath)
	int getAbsoluteValue(int num);

	float randomValueBetween(float low , float high);

	int randomValueBetween(int low , int high);

	std::string to_string(int value);
}

#endif