#include "TimeStop.h"

bool TimeStop::init()
{
	this->bindSprite(Sprite::create("TimeStop.png"));
	commandToCall = "TIME_STOP_FIVE_SECONDS";
	return true;
}
