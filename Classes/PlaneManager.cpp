#include "PlaneManager.h"
#include "Player.h"
#include "StringUtil.h"
#include "CsvUtil.h"

bool PlaneManager::init() {
	//从CSV中获取各机型数据
	const char* sPath = "plane.csv";
	CsvUtil::getInstance()->loadFile(sPath);
	for (int i = 1; i <= 9; i++) {
		m_rate[i] = CsvUtil::getInstance()->getValue(i, 6, sPath).asFloat();
		m_speedL[i] = CsvUtil::getInstance()->getValue(i, 4, sPath).asInt();
		m_speedR[i] = CsvUtil::getInstance()->getValue(i, 5, sPath).asInt();
		m_HP[i] = CsvUtil::getInstance()->getValue(i, 3, sPath).asInt();
		m_weightL[i] = CsvUtil::getInstance()->getValue(i, 7, sPath).asInt();
		m_weightR[i] = CsvUtil::getInstance()->getValue(i, 8, sPath).asInt();
		m_pathL[i] = CsvUtil::getInstance()->getValue(i, 1, sPath).asString();
		m_pathR[i] = CsvUtil::getInstance()->getValue(i, 2, sPath).asString();
		m_propRate[i] = CsvUtil::getInstance()->getValue(i, 9, sPath).asFloat();
	}

	this->scheduleUpdate();
	this->schedule(schedule_selector(PlaneManager::scheduleCreatePlane), 0.5f);
	return true;
}

void PlaneManager::createPlane(Point pos, int speed, Sprite* sprite, int HP, int grade, float propRate) {
	/* 新飞机参数设置 */
	EnemyPlane* newPlane = EnemyPlane::create();
    newPlane->bindSprite(sprite);
	newPlane->setPosition(pos);
	newPlane->setSpeed(speed);
	newPlane->setHP(HP);
	newPlane->setGrade(grade);
	newPlane->setPropRate(propRate);
	count++;
	this->addChild(newPlane);
	m_planeVec.pushBack(newPlane);
}

void PlaneManager::update(float dt) {
	for (auto i : m_planeVec) {
		if (i->isFlying()) {
			/* 移动飞机 */
			i->setPositionX(i->getPositionX() + int(i->getSpeed() * m_speedTimes));
			if (i->getPositionX() < -230 || i->getPositionX() > 961 ) {
				i->hide();
				m_planeVec.eraseObject(i);
			}
		}		
	}
}

int PlaneManager::getCount() {
	return count;
}

//void PlaneManager::setCoolingTimeEnd(float dt) {
//	m_coolingTime = false;
//}

void PlaneManager::scheduleCreatePlane(float dt) {
	//用随机函数产生随机机型飞机
	float ran = CCRANDOM_0_1();	
	int i = 1;
	while (i <= 9) {	//遍历各机型，用概率分布获取机型
		if (m_rate[i] >= ran) {
			float ranDirection = CCRANDOM_0_1();	//获取飞行方向
			bool isLeft = (ranDirection <= 0.5);
			int speed = m_speedL[i] + CCRANDOM_0_1() * m_speedR[i];
			int grade = m_weightL[i] + CCRANDOM_0_1() * m_weightR[i];

			if (isLeft) {
				Point posL = Point(-230, 250 + CCRANDOM_0_1() * 260);
				createPlane(posL, speed, Sprite::create(m_pathL[i].c_str()), m_HP[i], grade, m_propRate[i]);
			}
			else {
				Point posR = Point(960, 250 + CCRANDOM_0_1() * 260);
				createPlane(posR, speed * (-1), Sprite::create(m_pathR[i].c_str()), m_HP[i], grade, m_propRate[i]);			
			}
			break;
		}
		else i++;
	}
	
}