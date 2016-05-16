#include "TollgateScene.h"
#include "Cartridge.h"
#include "EnemyPlane.h"
#include "PropManager.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

Scene* TollgateScene::createScene() 
{
    auto scene = Scene::create();
    auto layer = TollgateScene::create();
    scene->addChild(layer);
	return scene;
}

bool TollgateScene::init() 
{
    if (!Layer::init())
    {
        return false;
    }
	Size visibleSize = CCDirector::getInstance()->getVisibleSize();

	/* 创建主角 */
	m_player = Player::create();
	m_player->bindSprite(Sprite::create("sprite.png"));
	m_player->bindSpriteRight(Sprite::create("sprite_right.png"));
    m_player->setPosition(Point(visibleSize.width / 2 - 32, 31));
    this->addChild(m_player, 3);

	/* 初始化背景图片 */
	initBG();
	oddTime = originTime = 3660;
   
    /* 创建管理器 */
    m_cartridgeManager = CartridgeManager::create();
    this->addChild(m_cartridgeManager, 2);
	m_planeManager = PlaneManager::create();
	this->addChild(m_planeManager, 3);
	m_propManager = PropManager::create();
	this->addChild(m_propManager, 2);
	m_cartridgeManager->bindPlayer(m_player);
	m_cartridgeManager->bindPlaneManager(m_planeManager);
	m_propManager->bindPlayer(m_player);
	m_cartridgeManager->bindPropManager(m_propManager);

	/* 加载定时器 */
    this->scheduleUpdate();
	loadUI();

    return true;
}

void TollgateScene::initBG() 
{
    Size visibleSize = CCDirector::getInstance()->getVisibleSize();
    m_bgSprite1 = Sprite::create("tollgateBG.jpg");
    m_bgSprite1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(m_bgSprite1, 0);
}

void TollgateScene::update(float delta)
{
	if (KEY_DOWN(VK_LEFT)) {	//激活鼠标左键事件
		m_player->moveToLeft(m_player->getSpeed());
	}
	if (KEY_DOWN(VK_RIGHT)) {	//激活鼠标右键事件
		m_player->moveToRight(m_player->getSpeed());
	}
	if (KEY_DOWN(VK_SPACE)) {	//激活空格事件
		m_cartridgeManager->createCartridge(Point((m_player->getPositionX()) + 32, 130));
	}
	
	/* 游戏剩余时间刷新 */
	oddTime--;	
	m_player->t_carom->setText(Value(oddTime / 60).asString());
	m_player->m_gradeBar->setPercent(oddTime * 100 / (originTime-60));
	if (oddTime < 0) {
		auto gameOverScene = GameOver::createScene(m_player->getGrade());
		Director::getInstance()->replaceScene(TransitionSlideInL::create(0.3f, gameOverScene));
	}

	/* 处理道具事件 */
	loadCallFromPlayer();
}

void TollgateScene::loadCallFromPlayer() {
	if (m_player->getIsGettingProps()) {
		std::string command = m_player->getCall();
		m_player->clearPropCall();	//清除指令
		if (command == "CLOCK_ADD_FIVE_SECONDS") {	//加时道具
			oddTime += 300;
			if (oddTime > 3600) oddTime = 3600;
		}
		if (command == "TIME_STOP_FIVE_SECONDS") {	//时间凝固道具
			m_planeManager->m_speedTimes = 0;
			m_props.at(0)->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("5s.wav");
			this->unschedule(schedule_selector(TollgateScene::TimeStopReload));
			this->scheduleOnce(schedule_selector(TollgateScene::TimeStopReload), 5.0f);
		}
		if (command == "MUL2_FIVE_SECONDS") {	//双倍道具
			m_player->setGradeTimes(m_player->getGradeTimes() * 2);
			m_props.at(1)->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("5s.wav");
			this->unschedule(schedule_selector(TollgateScene::Mul2Reload));
			this->scheduleOnce(schedule_selector(TollgateScene::Mul2Reload), 5.0f);
		}
		if (command == "RUSH_FIVE_SECONDS") {	//子弹冲刺道具
			m_cartridgeManager->m_coolingTimeInterval = 0.1f;
			m_props.at(2)->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("5s.wav");
			this->unschedule(schedule_selector(TollgateScene::RushReload));
			this->scheduleOnce(schedule_selector(TollgateScene::RushReload), 5.0f);
			
		}
		if (command == "BOMB_IS_GOING_TO_BOOM") {	//炸弹道具
			if (m_props.at(3)->isVisible() == false) {
				oddTime = 59;
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Bomb.wav");
			}			
		}
		if (command == "PROTECT_FIVE_SECONDS") {	//保护盾道具
			m_props.at(3)->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("5s.wav");
			this->unschedule(schedule_selector(TollgateScene::ProtectReload));
			this->scheduleOnce(schedule_selector(TollgateScene::ProtectReload), 5.0f);
		}
	}
}

void TollgateScene::TimeStopReload( float dt ) {	
	m_planeManager->m_speedTimes = 1.0f;
	m_props.at(0)->setVisible(false);
}

void TollgateScene::Mul2Reload(float dt) {
	m_player->setGradeTimes(m_player->getGradeTimes() / 2);
	m_props.at(1)->setVisible(false);
}

void TollgateScene::RushReload(float dt) {
	m_cartridgeManager->m_coolingTimeInterval = 0.3f;
	m_props.at(2)->setVisible(false);
}

void TollgateScene::ProtectReload(float dt) {
	m_props.at(3)->setVisible(false);
}

void TollgateScene::loadUI()
{
	/* 加载游戏数据显示 */
	auto rootNode = CSLoader::createNode("Dataload.csb");
	addChild(rootNode,5);
	m_player->t_scene = (Text*)rootNode->getChildByName("Scene");
	m_player->t_carom = (Text*)rootNode->getChildByName("Carom");
	m_player->t_grade = (Text*)rootNode->getChildByName("Grade");
	//m_player->t_scene_size = m_player->t_scene->getContentSize();
	m_player->m_gradeBar = (LoadingBar*)rootNode->getChildByName("GradeBar");
	m_player->t_grade->setText("0");
	m_player->t_scene->setText("");
	m_player->t_carom->setText("");
	m_player->m_gradeBar->setPercent(0);

	/* 加载道具指示 */
	m_props.pushBack(Sprite::create("TimeStop.png"));
	m_props.at(0)->setPosition(Point(350, 600));
	this->addChild(m_props.at(0), 5);
	m_props.pushBack(Sprite::create("Mul2.png"));
	m_props.at(1)->setPosition(Point(415, 600));
	this->addChild(m_props.at(1), 5);
	m_props.pushBack(Sprite::create("Rush.png"));
    m_props.at(2)->setPosition(Point(480, 600));
	this->addChild(m_props.at(2), 5);
	m_props.pushBack(Sprite::create("protect.png"));
	m_props.at(3)->setPosition(Point(545, 600));
	this->addChild(m_props.at(3), 5);
	m_props.at(0)->setVisible(false);
	m_props.at(1)->setVisible(false);
	m_props.at(2)->setVisible(false);
	m_props.at(3)->setVisible(false);

}


