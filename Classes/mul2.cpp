#include "Mul2.h"

bool Mul2::init()
{
	this->bindSprite(Sprite::create("Mul2.png"));
	commandToCall = "MUL2_FIVE_SECONDS";
	return true;
}
