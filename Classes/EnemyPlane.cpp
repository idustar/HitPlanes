#include "EnemyPlane.h"

EnemyPlane::EnemyPlane()
{
	m_isFlying = true;
	m_grade = 1;
}

EnemyPlane::~EnemyPlane()
{
}

bool EnemyPlane::init()
{
	return true;
}

void EnemyPlane::resetData(Point pos) {
	if (getSprite() != NULL) {
		setPosition(pos);
	}
}

void EnemyPlane::show() {
	if (getSprite() != NULL) {
		setVisible(true);
		m_isFlying = true;
	}
}

void EnemyPlane::hide() {
	if (getSprite() != NULL) {
		setVisible(false);
		m_isFlying = false;
	}
}

bool EnemyPlane::isFlying() {
	return m_isFlying;
}

void EnemyPlane::setHP(int HP) {
	m_HP = HP;
}

int EnemyPlane::getHP() {
	return m_HP;
}

int EnemyPlane::getSpeed() {
	return m_speed;
}

void EnemyPlane::setSpeed(int speed) {
	m_speed = speed;
}

int EnemyPlane::hit(int HPMinus) {
	if (m_HP > 0) {
		m_HP = m_HP - HPMinus;
		if (m_HP <= 0) {
			auto fadeout = FadeOut::create(0.4f);
			auto rotate= RotateTo::create(0.4f, 180, 20);
            auto endAction = [&]() {
				hide();
				setVisible(false);
			};
			/* 击落动画 */
			CallFunc *endAct = CallFunc::create(endAction);
			Action* actions = Sequence::create(Spawn::create( 
				fadeout, rotate, NULL), endAct, NULL);
			m_sprite->runAction(actions);
			return 0;	//有效且消灭
		}
		auto scale = ScaleBy::create(0.1f, 1.2f, 1.2f);
		auto actions = Sequence::create(scale, scale->reverse(), NULL);
		m_sprite->runAction(actions);
		return 1;	//有效但未消灭
	}
	return -1;	//无效
}

int EnemyPlane::getGrade() {
	return m_grade;
}

void EnemyPlane::setGrade(int grade) {
	m_grade = grade;
}

float EnemyPlane::getPropRate() {
	return m_propRate;
}

void EnemyPlane::setPropRate(float propRate) {
	m_propRate = propRate;
}