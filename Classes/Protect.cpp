#include "Protect.h"

bool Protect::init()
{
	this->bindSprite(Sprite::create("protect.png"));
	commandToCall = "PROTECT_FIVE_SECONDS";
	return true;
}
