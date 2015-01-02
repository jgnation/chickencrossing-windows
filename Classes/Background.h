#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SpriteContainer.h"
#include <string>

class Background : public SpriteContainer
{
public:
	Background();
	~Background(void);
	static Background* create(std::string backgroundFileName);
	virtual bool init(std::string backgroundFileName);
};

#endif