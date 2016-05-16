#ifndef __Clock_H__
#define __Clock_H__

#include "cocos2d.h"
#include "Prop.h"
using namespace cocos2d;

class Clock : public Prop {
public:
	CREATE_FUNC(Clock);
	virtual bool init();
};

#endif
