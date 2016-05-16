#include "TollgateScene.h"
#include "Cartridge.h"
#include "EnemyPlane.h"
#include "PropManager.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "json\writer.h"
#include "json\reader.h"
#include "json\value.h"

Scene* TollgateScene::createScene(int tempRecord) 
{
    auto scene = Scene::create();
    auto layer = TollgateScene::create();
	layer->tempRecord = tempRecord;
	log("%d", tempRecord);
    scene->addChild(layer);
	return scene;
}

bool TollgateScene::init() 
{
	log("start init");
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
	//m_player->m_record = tempRecord;
    this->addChild(m_player, 3);

	/* 初始化背景图片 */
	initBG();
	oddTime = originTime = 3660;
	log("Are you beautiful?");
   
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
	//loadText("I love you. You are my sunshine", 2.0f);

	/* 加载定时器 */
	log("new Game");
	readJson();
	loadUI();

	this->scheduleUpdate();
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
		if (m_player->getGrade() > m_player->m_record) {
			m_player->m_record = m_player->getGrade();
			setJson(); 
		}
		auto gameOverScene = GameOver::createScene(m_player->getGrade(), m_player->m_record);
		Director::getInstance()->replaceScene(gameOverScene);
			//TransitionSlideInL::create(0.3f, gameOverScene));
	}

	/* 道具剩余时间刷新 */
	for (int i = 0; i < 4; i++) {
		if (m_propOddTime[i] > 0) {
			m_propOddTime[i]--;
			m_propBars.at(i)->setPercent(m_propOddTime[i] / 3);
		}
	}
	if (m_propOddTime[0] == 1) TimeStopReload(0.0f);
	else if (m_propOddTime[1] == 1) Mul2Reload(0.0f);
	else if (m_propOddTime[2] == 1) RushReload(0.0f);
	else if (m_propOddTime[3] == 1) ProtectReload(0.0f);



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
			loadText("Now you get 5 seconds more.", 1.0f);
		}
		if (command == "TIME_STOP_FIVE_SECONDS") {	//时间凝固道具
			m_planeManager->m_speedTimes = 0;
			m_props.at(0)->setVisible(true);
			m_propBars.at(0)->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("5s.wav");
			m_propOddTime[0] = 300;
			//this->unschedule(schedule_selector(TollgateScene::TimeStopReload));
			//this->scheduleOnce(schedule_selector(TollgateScene::TimeStopReload), 5.0f);
			loadText("All flyers will be frozen in 5 seconds.", 2.0f);
		}
		if (command == "MUL2_FIVE_SECONDS") {	//双倍道具
			m_player->setGradeTimes(m_player->getGradeTimes() * 2);
			m_props.at(1)->setVisible(true);
			m_propBars.at(1)->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("5s.wav");
			m_propOddTime[1] = 300;
			m_player->t_grade->setTextColor(ccc4(255, 0, 0, 255));
			//this->unschedule(schedule_selector(TollgateScene::Mul2Reload));
			//this->scheduleOnce(schedule_selector(TollgateScene::Mul2Reload), 5.0f);
			loadText("Scores will be double in 5 seconds.", 2.0f);
		}
		if (command == "RUSH_FIVE_SECONDS") {	//子弹冲刺道具
			m_cartridgeManager->m_coolingTimeInterval = 0.1f;
			m_props.at(2)->setVisible(true);
			m_propBars.at(2)->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("5s.wav");
			m_propOddTime[2] = 300;
			//this->unschedule(schedule_selector(TollgateScene::RushReload));
			//this->scheduleOnce(schedule_selector(TollgateScene::RushReload), 5.0f);
			loadText("You can throw coke cans more smoothly in 5 seconds.", 2.0f);
			
		}
		if (command == "BOMB_IS_GOING_TO_BOOM") {	//炸弹道具
			if (m_props.at(3)->isVisible() == false) {
				oddTime = 59;
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Bomb.wav");
				loadText("Bye-bye!", 1.0f);
			}			
		}
		if (command == "PROTECT_FIVE_SECONDS") {	//保护盾道具
			m_props.at(3)->setVisible(true);
			m_propBars.at(3)->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("5s.wav");
			m_propOddTime[3] = 300;
			//this->unschedule(schedule_selector(TollgateScene::ProtectReload));
			//this->scheduleOnce(schedule_selector(TollgateScene::ProtectReload), 5.0f);
			loadText("You can be protected from coke cans in 5 seconds.", 2.0f);
		}
	}
}

void TollgateScene::TimeStopReload(float dt) {	
	m_planeManager->m_speedTimes = 1.0f;
	m_props.at(0)->setVisible(false);
	m_propBars.at(0)->setVisible(false);

}

void TollgateScene::Mul2Reload(float dt) {
	m_player->setGradeTimes(m_player->getGradeTimes() / 2);
	if (m_player->isNewRecord)
		m_player->t_grade->setTextColor(ccc4(0, 255, 0, 255));
	else
		m_player->t_grade->setTextColor(ccc4(255, 255, 255, 255));
	m_props.at(1)->setVisible(false);
	m_propBars.at(1)->setVisible(false);
}

void TollgateScene::RushReload(float dt) {
	m_cartridgeManager->m_coolingTimeInterval = 0.3f;
	m_props.at(2)->setVisible(false);
	m_propBars.at(2)->setVisible(false);
}

void TollgateScene::ProtectReload(float dt) {
	m_props.at(3)->setVisible(false);
	m_propBars.at(3)->setVisible(false);
}

void TollgateScene::loadUI()
{
	/* 加载游戏数据显示 */
	auto rootNode = CSLoader::createNode("Dataload.csb");
	addChild(rootNode,5);
	m_player->t_scene = (Text*)rootNode->getChildByName("Scene");
	m_player->t_carom = (Text*)rootNode->getChildByName("Carom");
	m_player->t_grade = (Text*)rootNode->getChildByName("Grade");
	m_player->t_highestScore = (Text*)rootNode->getChildByName("high");
	//m_player->t_scene_size = m_player->t_scene->getContentSize();
	m_player->m_gradeBar = (LoadingBar*)rootNode->getChildByName("GradeBar");
	m_player->t_grade->setText("0");
	m_player->t_scene->setText("");
	m_player->t_carom->setText("");
	m_player->t_highestScore->setText("RECORD " + Value(m_player->m_record).asString());
	//m_player->t_highestScore->setText("RECORD ");
	m_player->m_gradeBar->setPercent(0);

	/* 加载道具指示 */
	//m_props.pushBack(Sprite::create("TimeStop.png"));
	//m_props.at(0)->setPosition(Point(350, 600));
	m_props.pushBack((Sprite*)rootNode->getChildByName("IMG1"));
	m_propBars.pushBack((LoadingBar*)rootNode->getChildByName("BAR1"));
	this->addChild(m_props.at(0), 5);
	this->addChild(m_propBars.at(0), 5);
	//m_props.pushBack(Sprite::create("Mul2.png"));
	//m_props.at(1)->setPosition(Point(415, 600));
	m_props.pushBack((Sprite*)rootNode->getChildByName("IMG2"));
	m_propBars.pushBack((LoadingBar*)rootNode->getChildByName("BAR2"));
	this->addChild(m_props.at(1), 5);
	this->addChild(m_propBars.at(1), 5);
	//m_props.pushBack(Sprite::create("Rush.png"));
    //m_props.at(2)->setPosition(Point(480, 600));
	m_props.pushBack((Sprite*)rootNode->getChildByName("IMG3"));
	m_propBars.pushBack((LoadingBar*)rootNode->getChildByName("BAR3"));
	this->addChild(m_props.at(2), 5);
	this->addChild(m_propBars.at(2), 5);
	//m_props.pushBack(Sprite::create("protect.png"));
	//m_props.at(3)->setPosition(Point(545, 600));
	m_props.pushBack((Sprite*)rootNode->getChildByName("IMG4"));
	m_propBars.pushBack((LoadingBar*)rootNode->getChildByName("BAR4"));
	this->addChild(m_props.at(3), 5);
	this->addChild(m_propBars.at(3), 5);
}

void TollgateScene::loadText(std::string text, float dt) {
	Text* txt = Text::create(text, "arial" , 25);
	txt->setTextHorizontalAlignment(TextHAlignment::CENTER);
	txt->setPosition(Point(480, 550));
	this->addChild(txt, 6);
	auto fadeout = FadeOut::create(dt);
	auto moveby = MoveBy::create(dt, Point(0, 30));
	txt->runAction(Sequence::create(Spawn::create(
		fadeout, moveby, NULL), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, txt)), NULL));	
}

void TollgateScene::readJson() {
	Json::Reader reader;
	Json::Value root;
	std::string data = FileUtils::getInstance()->getStringFromFile("data.json");;
	if (reader.parse(data, root, false) == true) {
		log("haha3");
		//m_player->m_record = 0;
		int s1 = root["g1"].asInt() * root["g7"].asInt();
		int s2 = root["g4"].asInt() * root["g5"].asInt();
		int s3 = root["g3"].asInt() * root["g10"].asInt();
		int s4 = (root["g2"].asInt() - root["g6"].asInt()) * root["g12"].asInt();
		int s5 = root["g11"].asInt() * root["g9"].asInt();
		log("JSON S1 %d", root["g1"].asInt());
		if (root["g8"].asInt() == s1 + s2 - s3 - s4 + s5) {
			int record = s1 - s2 + s3 - s4 + s5;
			if (tempRecord < record) m_player->m_record = record; else m_player->m_record = tempRecord;
		}
		log("%d,%d,%d,%d,%d", s1, s2, s3, s4, s5);
	}
	log("%d", m_player->m_record);
	
}

void TollgateScene::setJson() {
	log("set Json %d", m_player->m_record);
	Json::Value root;
	Json::FastWriter writer;
	int k1 = CCRANDOM_0_1() * 100; 
	int k2 = CCRANDOM_0_1() * 100000;
	int k3 = CCRANDOM_0_1() * 1000;
	int k4 = CCRANDOM_0_1() * 1000;
	int k5 = CCRANDOM_0_1() * 100;
	int k6 = CCRANDOM_0_1() * 100000;
	int k7 = CCRANDOM_0_1() * 100;
	int k9 = 1;
	int k10 = CCRANDOM_0_1() * 100;
	int k12 = CCRANDOM_0_1() * 5;
	int s1 = k1 * k7;
	int s2 = k4 * k5;
	int s3 = k3 * k10;
	int s4 = (k2 - k6) * k12;
	int k11 = m_player->m_record + s2 + s4 - s1 - s3;
	int k8 = s1 + s2 - s3 - s4 + k11;
	root["g1"] = k1;
	root["g2"] = k2;
	root["g3"] = k3;
	root["g4"] = k4;
	root["g5"] = k5;
	root["g6"] = k6;
	root["g7"] = k7;
	root["g8"] = k8;
	root["g9"] = k9;
	root["g10"] = k10;
	root["g11"] = k11;
	root["g12"] = k12;
	std::string json_file = writer.write(root);
	FILE *file = fopen("data.json", "w");
	fprintf(file, json_file.c_str());
	fclose(file);

	//int s5 = root["g11"].asInt() * root["g9"].asInt();
	
}


