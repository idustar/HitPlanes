#include "Cartridge.h"

Cartridge::Cartridge()
{
	m_isFlying = true;
	hit = 1;
	
}

Cartridge::~Cartridge()
{
}

bool Cartridge::init()
{

	return true;
}

void Cartridge::resetData(Point pos) {
	if (getSprite() != NULL) {
		setPosition(pos);
	}
}
void Cartridge::show() {
	if (getSprite() != NULL) {
		setVisible(true);
		m_isFlying = true;
	}
}

void Cartridge::hide() {
	if (getSprite() != NULL) {
		setVisible(false);
		m_isFlying = false;
	}
}

bool Cartridge::isFlying() {
	return m_isFlying;
}

bool Cartridge::isCollideWithPlane(EnemyPlane* enemyPlane) {	//Åö×²¼ì²â
	Rect entityRect = enemyPlane->getBoundingBox();
	Point cartridgePos = getPosition();
	return entityRect.containsPoint(cartridgePos);
}