#ifndef __Player_H__
#define __Player_H__

#include "cocos2d.h"
#include "Entity.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;

class Player : public Entity {
public:
    Player();
    ~Player();
    CREATE_FUNC(Player);
    virtual bool init();
	void moveToLeft(int playerMoveSpeed);
	void moveToRight(int playerMoveSpeed);
	void bindSpriteRight(Sprite* sprite);
	int getSpeed();
	void setSpeed(int speed);
	int getGrade();
	void setGrade(int grade);
	float getGradeTimes();
	void setGradeTimes(float gradeTimes);
	Text* t_carom;
	Text* t_scene;
	Text* t_grade;
	Text* t_highestScore;
	int m_record;
	bool isNewRecord = false;
	LoadingBar* m_gradeBar;
	int getCarom();
	void setCarom(int carom);
	bool isCaroming;
	void propCall(std::string command);
	bool getIsGettingProps();
	std::string getCall();
	void clearPropCall();

private:
    void resetData();
	Sprite* m_spriteRight;
	int m_speed = 15;	//人物移动速度
	int m_grade;	//记录积分，应用score，我错了(。﹏。*)
	int m_carom = 0;	//连击次数
	float m_gradeTimes = 1.0f;	//积分倍数
	bool isGettingProps;	//是否获得道具指令
	std::string propCommand;	//回传的道具指令
	
};

#endif