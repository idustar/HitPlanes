#include "PropManager.h"
#include "SimpleAudioEngine.h"
#include "Clock.h"
#include "TimeStop.h"
#include "Mul2.h"
#include "Rush.h"
#include "Bomb.h"
#include "Protect.h"
#define CREATEPROPTYPE(type) type* prop = type::create();

bool PropManager::init() {
	this->scheduleUpdate();
	return true;
}

void PropManager::createProp(Point pos) {
	float ran = CCRANDOM_0_1();
	if (ran <= 0.75) {	//75%概率为炸弹道具
        CREATEPROPTYPE(Bomb);
		prop->setPosition(pos);
		prop->bindPlayer(m_player);
		this->addChild(prop);
		m_propVec.pushBack(prop);
	}
	else if (ran <= 0.8) {	//5%概率为保护盾道具
		CREATEPROPTYPE(Protect);
		prop->setPosition(pos);
		prop->bindPlayer(m_player);
		this->addChild(prop);
		m_propVec.pushBack(prop);
	}
	else if (ran <= 0.85) {	//5%概率为时间凝固道具
		CREATEPROPTYPE(TimeStop);
		prop->setPosition(pos);
		prop->bindPlayer(m_player);
		this->addChild(prop);
		m_propVec.pushBack(prop);
	}
	else if (ran <= 0.9) {	//5%概率为加时道具
		CREATEPROPTYPE(Clock);
		prop->setPosition(pos);
		prop->bindPlayer(m_player);
		this->addChild(prop);
		m_propVec.pushBack(prop);
	}
	else if (ran <= 0.95) {	//5%概率为子弹冲刺道具
		CREATEPROPTYPE(Rush);
		prop->setPosition(pos);
		prop->bindPlayer(m_player);
		this->addChild(prop);
		m_propVec.pushBack(prop);
	}
	else if (ran <= 1.0) {	//5%概率为双倍道具
		CREATEPROPTYPE(Mul2);
		prop->setPosition(pos);
		prop->bindPlayer(m_player);
		this->addChild(prop);
		m_propVec.pushBack(prop);
	}
}

void PropManager::update(float dt) {
	for (auto i : m_propVec) {
		/* 设置初始位置 */
		if (i->isFlying()) {

			i->setPositionY(i->getPositionY() - m_moveSpeed);

			if (i->getPositionY() <= 20) {
				hitMissed();
				i->hide();
				m_propVec.eraseObject(i);
			}

			if (i->isCollideWithPlayer(m_player)) {
				hitSucceed();
				i->doit();
				CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("mission.wav");
				i->hide();
				m_propVec.eraseObject(i);			
			}
		}
	}	
}

void PropManager::bindPlayer(Player* player) {
	m_player = player;
}

void PropManager::hitMissed() {	
}

void PropManager::hitSucceed() {
}
