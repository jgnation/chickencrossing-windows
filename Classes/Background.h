#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SpriteContainer.h"
#include <string>

class Background : public SpriteContainer
{
public:
	Background(std::string backgroundFileName);
	~Background(void);
};

#endif