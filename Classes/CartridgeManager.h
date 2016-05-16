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
	void createCartridge(Point pos);	//�����ӵ�
	void setCoolingTimeEnd(float dt);	//��ȴʱ�����	
	void bindPlayer(Player* player);
	float m_coolingTimeInterval = 0.3f;	//�ӵ���ȴʱ��
	//void bindBackScene(TollgateScene* backScene);
private:
	Vector<Cartridge*> m_cartridgeVec;
	int count = 0;
	bool m_coolingTime = false;	//�ӵ��Ƿ���ȴ��
	int m_moveSpeed = 25;	//�ӵ��ٶ�
	PlaneManager* m_planeManager;
	PropManager* m_propManager;
	Player* m_player;
	void hitMissed();
	void hitSucceed();
	//TollgateScene* m_backScene;
};

#endif