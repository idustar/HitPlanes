#ifndef __Cartridge_H__
#define __Cartridge_H__

#include "cocos2d.h"
#include "Entity.h"
#include "EnemyPlane.h"

using namespace cocos2d;

class Cartridge : public Entity {
public:
	Cartridge();
	~Cartridge();
	CREATE_FUNC(Cartridge);
	virtual bool init();
	void show();
	void hide();
	bool isFlying();
	void resetData(Point pos);
	bool isCollideWithPlane(EnemyPlane* plane);
	int hit;

private:
	bool m_isFlying;
};

#endif
