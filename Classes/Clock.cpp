#include "Clock.h"

bool Clock::init()
{
	this->bindSprite(Sprite::create("clock.png"));
	commandToCall = "CLOCK_ADD_FIVE_SECONDS";
	return true;
}
