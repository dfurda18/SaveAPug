#pragma once

#include "Entity.h"

#define MAX_LIVES 6

enum class BrickColour {BLUE, GREEN, GREY, BLACK, RED, YELLOW};

//externed sprites
extern Sprite *blueBrickSprite[6];
extern Sprite *greenBrickSprite[6];
extern Sprite *greyBrickSprite[6];
extern Sprite *blackBrickSprite[6];
extern Sprite *redBrickSprite[6];
extern Sprite *yellowBrickSprite[6];
extern int level;

class BrickEntity : public Entity
{
public:
	int lives;
	BrickColour colour;
	BrickEntity()
	{
		lives = MAX_LIVES;
		typeID = ENTITYBRICK;
		colour = BrickColour::BLUE;
	}

	bool HandleCollision();
};

BrickEntity * MakeBrick(BrickColour type, float xpos, float ypos);
BrickColour getColour(int colourNumber);