#ifndef __EnemyPlane_H__
#define __EnemyPlane_H__

#include "cocos2d.h"
#include "Entity.h"
using namespace cocos2d;

class EnemyPlane : public Entity {
public:
	EnemyPlane();
	~EnemyPlane();
	CREATE_FUNC(EnemyPlane);
	virtual bool init();
	void show();
	void hide();
	bool isFlying();
	void resetData(Point pos);
	int getHP();
	void setHP(int HP);
	int getSpeed();
	void setSpeed(int speed);
	int hit(int HPMimus);
	int getGrade();
	void setGrade(int grade);
	float getPropRate();
	void setPropRate(float propRate);

private:
	bool m_isFlying;
	int m_HP;
	int m_speed;
	int m_grade;
	float m_propRate; //出现道具概率

};

#endif
