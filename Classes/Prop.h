#ifndef __Prop_H__
#define __Prop_H__

#include "cocos2d.h"
#include "Entity.h"
#include "Player.h"
using namespace cocos2d;

class Prop : public Entity {
public:
	Prop();
	~Prop();
	CREATE_FUNC(Prop);
	virtual bool init();
	void show();
	void hide();
	bool isFlying();
	void resetData(Point pos);
	bool isCollideWithPlayer(Player* player);
	void doit();
	void bindPlayer(Player* player);
protected:
	bool m_isFlying;
	Player* m_player;
	std::string commandToCall;
};

#endif
