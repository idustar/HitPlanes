#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TollgateScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();  
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}


bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
	auto tipText = rootNode->getChildByName("Text_1");
	auto blink = Blink::create(5000, 10000);
	tipText->runAction(blink);
	this->scheduleUpdate();
    return true;
}



void HelloWorld::update(float delta) {
	if (KEY_DOWN(VK_SPACE)) {	//处理空格事件
		auto scene = TollgateScene::createScene(0);
		Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, scene));
		this->unscheduleUpdate();
	}
}