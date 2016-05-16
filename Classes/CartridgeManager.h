#pragma once
#ifndef _CartridgeManager_H_
#define _CartridgeManager_H_

#include "cocos2d.h"
#include "Cartridge.h"
#include "PlaneManager.h"
#include "Player.h"
#include "PropManager.h"
USING_NS_CC;

class CartridgeManager : public Node {
public:
	CREATE_FUNC(CartridgeManager);
	virtual bool init();
	void bindPlaneManager(PlaneManager* planeManager);
	void bindPropManager(PropManager* propManager);
	virtual void update(float dt);
	int getCount();
	void createCartridge(Point pos);	//创建子弹
	void setCoolingTimeEnd(float dt);	//冷却时间结束	
	void bindPlayer(Player* player);
	float m_coolingTimeInterval = 0.3f;	//子弹冷却时间
	//void bindBackScene(TollgateScene* backScene);
private:
	Vector<Cartridge*> m_cartridgeVec;
	int count = 0;
	bool m_coolingTime = false;	//子弹是否冷却中
	int m_moveSpeed = 25;	//子弹速度
	PlaneManager* m_planeManager;
	PropManager* m_propManager;
	Player* m_player;
	void hitMissed();
	void hitSucceed();
	//TollgateScene* m_backScene;
};

#endif