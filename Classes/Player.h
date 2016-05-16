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
	int m_speed = 15;	//�����ƶ��ٶ�
	int m_grade;	//��¼���֣�Ӧ��score���Ҵ���(���n��*)
	int m_carom = 0;	//��������
	float m_gradeTimes = 1.0f;	//���ֱ���
	bool isGettingProps;	//�Ƿ��õ���ָ��
	std::string propCommand;	//�ش��ĵ���ָ��
	
};

#endif