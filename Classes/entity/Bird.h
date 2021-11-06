#ifndef _BIRD_H__
#define _BIRD_H__

#include "cocos2d.h"
#include "Definitions.h"

class Bird
{
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *flappyBird;
	bool isGoingUp;
public:
	Bird(cocos2d::Layer *layer);
	void fly();
	void raise();
	void fall();
};

#endif
