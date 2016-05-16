#ifndef __TimeStop_H__
#define __TimeStop_H__

#include "cocos2d.h"
#include "Prop.h"
using namespace cocos2d;

class TimeStop : public Prop {
public:
	CREATE_FUNC(TimeStop);
	virtual bool init();
};

#endif
