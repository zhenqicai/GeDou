#ifndef __HERO_SELECT_LAYER_H__
#define __HERO_SELECT_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class HeroSelectLayer : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HeroSelectLayer);
};

#endif
