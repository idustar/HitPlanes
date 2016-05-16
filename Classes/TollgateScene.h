#ifndef __TollgateScene_H__
#define __TollgateScene_H__


#include "cocos2d.h"
//#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <windows.h>
#include "CartridgeManager.h"
#include "PlaneManager.h"
#include "PropManager.h"
#include "Player.h"

USING_NS_CC;

#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;
//USING_NS_CC_EXT;

class Player;
class TollgateScene : public Layer {
public:
    static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TollgateScene);

    virtual void update(float delta);
private:
    void initBG();          // 初始化关卡背景
    void loadUI();          // 加载UI
private:
	Sprite* m_bgSprite1;	// 背景精灵
	Player* m_player;		// 主角
	CartridgeManager* m_cartridgeManager;
	PlaneManager* m_planeManager;
	PropManager* m_propManager;
	Vector<Sprite*> m_props;	//道具提示
	int oddTime;	//剩余时间
	int originTime;	//总共时间
	void loadCallFromPlayer();
	void TimeStopReload(float dt);
	void Mul2Reload(float dt);
	void RushReload(float dt);
	void ProtectReload(float dt);
};

#endif