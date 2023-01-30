#include "BrickEntity.h"
#include "CollisionMask.h"

//Decide whether to change colour or die off:
//return true if this pbject should be removed
bool BrickEntity::HandleCollision()
{
	bool retval = false;
	this->lives = this->lives - (4-level);
	if (this->lives > 0)
	{
		switch (colour)
		{
		case BrickColour::BLUE:
			sprite = blueBrickSprite[MAX_LIVES - this->lives];
			break;
		case BrickColour::GREEN:
			sprite = greenBrickSprite[MAX_LIVES - this->lives];
			break;
		case BrickColour::GREY:
			sprite = greyBrickSprite[MAX_LIVES - this->lives];
			break;
		case BrickColour::BLACK:
			sprite = blackBrickSprite[MAX_LIVES - this->lives];
			break;
		case BrickColour::RED:
			sprite = redBrickSprite[MAX_LIVES - this->lives];
			break;
		case BrickColour::YELLOW:
			sprite = yellowBrickSprite[MAX_LIVES - this->lives];
			break;
		default: //because PURPLE wasn't handled yet, it will be handled by the default case
			retval = true;
			break;
		}
	}
	else {
		retval = true;
	}
	

	return retval;
}

extern b2World *world;

BrickEntity * MakeBrick(BrickColour type, float xpos, float ypos)
{
	BrickEntity *brickEntity = new BrickEntity();
	brickEntity->colour = type;

	//set the sprite to draw with
	switch (type)
	{
	case BrickColour::BLUE:
		brickEntity->sprite = blueBrickSprite[0];
		break;
	case BrickColour::GREEN:
		brickEntity->sprite = greenBrickSprite[0];
		break;
	case BrickColour::GREY:
		brickEntity->sprite = greyBrickSprite[0];
		break;
	case BrickColour::BLACK:
		brickEntity->sprite = blackBrickSprite[0];
		break;
	case BrickColour::RED:
		brickEntity->sprite = redBrickSprite[0];
		break;
	case BrickColour::YELLOW:
		brickEntity->sprite = yellowBrickSprite[0];
		break;
	}

	//make the physics body
	b2BodyDef brickBodyDef;

	//set the position of the center of the body, 
	//converting from pxel coords to physics measurements
	brickBodyDef.position.Set(xpos / PTM_RATIO, ypos / PTM_RATIO);
	brickBodyDef.type = b2_kinematicBody; //make it a kinematic body i.e. one moved by us

	//make the userdata point back to this entity
	brickBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(brickEntity);

	brickEntity->body = world->CreateBody(&brickBodyDef); //create the body and add it to the world

	// Define a box shape for our dynamic body.
	b2PolygonShape boxShape;
	//SetAsBox() takes as arguments the half-width and half-height of the box
	boxShape.SetAsBox(64.0f / (2.f*PTM_RATIO), 32.0f / (2.f*PTM_RATIO));

	b2FixtureDef brickFixtureDef;
	brickFixtureDef.shape = &boxShape;
	brickFixtureDef.density = 1.0f; //won't matter, as we made this kinematic
	brickFixtureDef.restitution = 0;
	brickFixtureDef.friction = 10.0f;

	//collison masking
	brickFixtureDef.filter.categoryBits = CMASK_BRICK;  //this is a brick
	brickFixtureDef.filter.maskBits = CMASK_BALL;		//it collides wth balls

	brickEntity->body->CreateFixture(&brickFixtureDef);
	
	return brickEntity;
}
BrickColour getColour(int colourNumber)
{
	switch (colourNumber)
	{
	case 0:
		return  BrickColour::BLUE;
	case 1:
		return  BrickColour::GREEN;
	case 2:
		return  BrickColour::GREY;
	case 3:
		return  BrickColour::BLACK;
	case 4:
		return  BrickColour::RED;
	case 5:
		return  BrickColour::YELLOW;
	}
}