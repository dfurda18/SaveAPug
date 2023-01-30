#pragma once

#include "Entity.h"

enum class PowerUpType { MULTIBALL, BIGGER_PADDLE, EXTRA_LIFE, KONG, TRAPPED_PUG };

class PowerUpEntity : public Entity
{
private:	

public:
	PowerUpType powerUpType;
	PowerUpEntity();
	void Update(float seconds);
};

PowerUpEntity * MakePowerUp(PowerUpType type, float xpos, float ypos);
int PowerUpValue(PowerUpType type);
PowerUpType FromValue(int type);