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
    void initBG();          // ��ʼ���ؿ�����
    void loadUI();          // ����UI
private:
	Sprite* m_bgSprite1;	// ��������
	Player* m_player;		// ����
	CartridgeManager* m_cartridgeManager;
	PlaneManager* m_planeManager;
	PropManager* m_propManager;
	Vector<Sprite*> m_props;	//������ʾ
	int oddTime;	//ʣ��ʱ��
	int originTime;	//�ܹ�ʱ��
	void loadCallFromPlayer();
	void TimeStopReload(float dt);
	void Mul2Reload(float dt);
	void RushReload(float dt);
	void ProtectReload(float dt);
};

#endif