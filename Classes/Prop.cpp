#include "Prop.h"

Prop::Prop()
{
	m_isFlying = true;
}

Prop::~Prop()
{
}

bool Prop::init()
{
	//this->bindSprite(Sprite::create("sprite.png"));
	return true;
}

void Prop::resetData(Point pos) {
	if (getSprite() != NULL) {
		setPosition(pos);
	}
}
void Prop::show() {
	if (getSprite() != NULL) {
		setVisible(true);
		m_isFlying = true;
	}
}

void Prop::hide() {
	if (getSprite() != NULL) {
		setVisible(false);
		m_isFlying = false;
	}
}

bool Prop::isFlying() {
	return m_isFlying;
}

bool Prop::isCollideWithPlayer(Player* player) {
	Rect entityRect = player->getBoundingBox();
	Point propPos = getPosition();
	return entityRect.containsPoint(propPos);
}

void Prop::doit() {
	/* 传输道具指令 */
	log("START CALLING");
	m_player->propCall(commandToCall);
	log("END CALLING");
}

void Prop::bindPlayer(Player* player) {
	m_player = player;
}