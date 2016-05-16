#include "CartridgeManager.h"
#include "SimpleAudioEngine.h"

bool CartridgeManager::init() {
	this->scheduleUpdate();

	return true;
}

void CartridgeManager::createCartridge(Point pos) {
	if (!m_coolingTime) {
		/* 创建子弹 */
		Cartridge* cart = Cartridge::create();
		cart->bindSprite(Sprite::create("cartridge.png"));
		cart->setPosition(pos);
		count++;
		this->addChild(cart);
		m_cartridgeVec.pushBack(cart);
		m_coolingTime = true;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("SE_CardSel.wav");
		/* 重新配置定时器*/
		this->scheduleOnce(schedule_selector(CartridgeManager::setCoolingTimeEnd), m_coolingTimeInterval);
	}
}

void CartridgeManager::update(float dt) {
	for (auto i : m_cartridgeVec) {
		if (i->isFlying()) {
			/* 子弹飞行处理 */
			i->setPositionY(i->getPositionY() + m_moveSpeed);

			/* 子弹浪费处理 */
			if (i->getPositionY() >= 640) {
				hitMissed();
				i->hide();
				m_cartridgeVec.eraseObject(i);
			}

			/* 子弹碰撞检测和处理 */
			for (auto plane : m_planeManager->m_planeVec) {
				if (i->isCollideWithPlane(plane)) {
					int hitReturn = plane->hit(i->hit);

					if (hitReturn == -1) { //无效击中
						hitMissed();//...
					}
					else if (hitReturn == 1) {	//击中但未击落
						hitSucceed();
						i->hide();
						m_cartridgeVec.eraseObject(i);
					}
					else if (hitReturn == 0) {	//击中并击落
						hitSucceed();
						//随机事件产生道具
						float ran = CCRANDOM_0_1();
						if (ran < plane->getPropRate()) {
							m_propManager->createProp(Point(
								plane->getPositionX() + plane->getContentSize().width / 2 - 25,
								plane->getPositionY() + plane->getContentSize().height / 2 - 25));
						}
						//积分更新
						m_player->setGrade(m_player->getGrade() + plane->getGrade() * m_player->getCarom() * m_player->getGradeTimes());
						m_player->t_grade->setText((Value(m_player->getGrade()).asString()));

						m_planeManager->m_planeVec.eraseObject(plane);
						i->hide();
						m_cartridgeVec.eraseObject(i);				
					}
				}
			}
		}		
	}
}

int CartridgeManager::getCount() {
	return count;
}

void CartridgeManager::bindPlayer(Player* player) {
	m_player = player;
}

void CartridgeManager::setCoolingTimeEnd(float dt) {	//冷却时间结束调用
	m_coolingTime = false;
}

void CartridgeManager::bindPlaneManager(PlaneManager* planeManager) {
	m_planeManager = planeManager;
}
void CartridgeManager::bindPropManager(PropManager* propManager) {
	m_propManager = propManager;
}

void CartridgeManager::hitMissed() {
	//连击数据清零
	m_player->setCarom(0);
	m_player->isCaroming = false;
	m_player->t_scene->setText("");
}

void CartridgeManager::hitSucceed() {
	//连击更新
	m_player->setCarom(m_player->getCarom() + 1);
	if (m_player->getCarom() == 1)
		m_player->isCaroming = true;
	else {
	m_player->t_scene->setText(Value("Carom X").asString() + Value(m_player->getCarom()).asString());
	}
}