#include "GameOverScene.h"
#include "TollgateScene.h"
#include "SimpleAudioEngine.h"

//USING_NS_CC;

//using namespace cocostudio::timeline;

Scene* GameOver::createScene(int score)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = GameOver::create();
	layer->m_score = score;
    // add layer as a child to scene
    scene->addChild(layer);
	//log("Here is you");
	//log("%d", layer->m_score);
	//log("Here is you");
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
		auto scene = TollgateScene::createScene();
		// run
		Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, scene));
	}
}

void GameOver::loadScore() {
	auto rootNode = CSLoader::createNode("GameOver.csb");
	addChild(rootNode);
	auto scorelabel = (Text*)rootNode->getChildByName("Score");
	scorelabel->setText(Value(m_score).asString());
	auto btn = (Button*)rootNode->getChildByName("btnReplay");
	btn->addTouchEventListener(this, toucheventselector(GameOver::replay));
}

void GameOver::replay(Ref*, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED:
		auto scene = TollgateScene::createScene();
		Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, scene));
		break;
	}
}