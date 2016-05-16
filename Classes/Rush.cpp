#include "Rush.h"

bool Rush::init()
{
	this->bindSprite(Sprite::create("Rush.png"));
	commandToCall = "RUSH_FIVE_SECONDS";
	return true;
}
