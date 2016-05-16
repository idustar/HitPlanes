#pragma once
#ifndef _PropManager_H_
#define _PropManager_H_

#include "cocos2d.h"
#include "Prop.h"
#include "Player.h"
USING_NS_CC;

class PropManager : public Node {
public:
	CREATE_FUNC(PropManager);
	virtual bool init();
	virtual void update(float dt);
	void createProp(Point pos);
	void bindPlayer(Player* player);
	
private:
	Vector<Prop*> m_propVec;
	Player* m_player;
	bool isFlying;
	int m_moveSpeed = 5;
	void hitMissed();
	void hitSucceed();
};

#endif
