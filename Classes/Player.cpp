#include "Player.h"

Player::Player() 
{
	m_grade = 0;
	isGettingProps = false;
}

Player::~Player() 
{
}

bool Player::init() 
{

    return true;
}

void Player::resetData() {
}

void Player::moveToLeft(int playerMoveSpeed = 1) {
	/* 处理向左移动 */
	int playerPositionX = this->getPositionX();
	this->m_sprite->setVisible(true);
	this->m_spriteRight->setVisible(false);
	playerPositionX -= playerMoveSpeed;
	if (playerPositionX >= 0 && playerPositionX <= 895)
	    this->setPositionX(playerPositionX);
}

void Player::moveToRight(int playerMoveSpeed = 1) {
	/* 处理向右移动 */
	int playerPositionX = this->getPositionX();
	this->m_sprite->setVisible(false);
	this->m_spriteRight->setVisible(true);
	playerPositionX += playerMoveSpeed;
	if (playerPositionX >= 0 && playerPositionX <= 895)
	    this->setPositionX(playerPositionX);
}

void Player::bindSpriteRight(Sprite* sprite)
{
	this->m_spriteRight = sprite;
	this->addChild(m_spriteRight);
	Size size = m_spriteRight->getContentSize();
	m_spriteRight->setPosition(Point(size.width * 0.5f, size.height * 0.5f));
	this->setContentSize(size);
	m_sprite->setVisible(false);
}

void Player::setSpeed(int speed) {
	m_speed = speed;
}

int Player::getSpeed() {
	return m_speed;
}

void Player::setGrade(int grade) {
	m_grade = grade;
}

int Player::getGrade() {
	return m_grade;
}

void Player::setGradeTimes(float gradeTimes) {
	m_gradeTimes = gradeTimes;
}

float Player::getGradeTimes() {
	return m_gradeTimes;
}

void Player::setCarom(int carom) {
	m_carom = carom;
}

int Player::getCarom() {
	return m_carom;
}

void Player::propCall(std::string command) {
	propCommand = command;
	isGettingProps = true;
}

bool Player::getIsGettingProps() {
	return isGettingProps;
}

std::string Player::getCall() {
	return propCommand;
}

void Player::clearPropCall() {
	propCommand = "";
	isGettingProps = false;
}