#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include <windows.h>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;

#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)

class GameOver : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int Score);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	
    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);
	virtual void update(float delta);
	int m_score;
	void loadScore();
	void replay(Ref*, TouchEventType type);
	//Text* scorelabel;
};

#endif // __HELLOWORLD_SCENE_H__
