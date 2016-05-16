#include "GameOverScene.h"
#include "TollgateScene.h"
#include "SimpleAudioEngine.h"

//USING_NS_CC;

//using namespace cocostudio::timeline;

Scene* GameOver::createScene(int score, int record)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = GameOver::create();
	layer->m_score = score;
	layer->m_record = record;
    // add layer as a child to scene
    scene->addChild(layer);
	layer->loadScore();
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("lose.wav");
	this->scheduleUpdate();
    return true;
}



void GameOver::update(float delta) {
	if (KEY_DOWN(VK_SPACE)) {
		log("new Game is going to create.");
		auto scene = TollgateScene::createScene(m_record);
		// run
		Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, scene));
		this->unscheduleUpdate();
	}
}

void GameOver::loadScore() {
	auto rootNode = CSLoader::createNode("GameOver.csb");
	addChild(rootNode);
	auto scorelabel = (Text*)rootNode->getChildByName("Score");
	scorelabel->setText(Value(m_score).asString());
	auto recordlabel = (Text*)rootNode->getChildByName("ScoreH");
	recordlabel->setText(Value(m_record).asString());
	auto btn = (Button*)rootNode->getChildByName("btnReplay");
	btn->addTouchEventListener(this, toucheventselector(GameOver::replay));
}

void GameOver::replay(Ref*, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED:
		log("new Game is going to create.");
		auto scene = TollgateScene::createScene(m_record);
		log("going to create.");
		Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, scene));
		log("gameover create end");
		break;
	}
}