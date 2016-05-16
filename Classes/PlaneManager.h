#pragma once
#ifndef _PlaneManager_H_
#define _PlaneManager_H_

#include "cocos2d.h"
#include "EnemyPlane.h"
USING_NS_CC;

class PlaneManager : public Node {
public:
	CREATE_FUNC(PlaneManager);
	virtual bool init();
	virtual void update(float dt);
	int getCount();	//获取飞机数目，事实证明这个函数没用
	void createPlane(Point pos, int speed, Sprite* sprite, int HP,int grade, float propRate);
	void scheduleCreatePlane(float dt);
	Vector<EnemyPlane*> m_planeVec;
	float m_speedTimes = 1.0f;	//速度倍率

private:
	int count = 0;	
	std::string m_pathL[10];
	std::string m_pathR[10];
	int m_HP[10];
	int m_speedL[10];
	int m_speedR[10];
	int m_weightL[10];
	float m_rate[10];
	int m_weightR[10];
	float m_propRate[10];

};

#endif