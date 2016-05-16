#include "Bomb.h"

bool Bomb::init()
{
	this->bindSprite(Sprite::create("Bomb.png"));
	commandToCall = "BOMB_IS_GOING_TO_BOOM";
	return true;
}
