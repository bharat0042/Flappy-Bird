#ifndef __REWARD_H__
#define __REWARD_H__

#include "cocos2d.h"
#include "Definitions.h"

class Reward
{
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

public:
	Reward();

	cocos2d::Sprite* spawnReward(cocos2d::Layer *layer, unsigned int level);
};

#endif
