#ifndef __Bomb_H__
#define __Bomb_H__

#include "cocos2d.h"
#include "Prop.h"
using namespace cocos2d;

class Bomb : public Prop {
public:
	CREATE_FUNC(Bomb);
	virtual bool init();
};

#endif
