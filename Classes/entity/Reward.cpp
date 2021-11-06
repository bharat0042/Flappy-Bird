#include "Reward.h"

Reward::Reward() :
	visibleSize{ cocos2d::Director::getInstance()->getVisibleSize() },
	origin{ cocos2d::Director::getInstance()->getVisibleOrigin() }
{
}

cocos2d::Sprite* Reward::spawnReward(cocos2d::Layer *layer, unsigned int level)
{
	auto reward = cocos2d::Sprite::create("images/Dollar.png");

	auto rewardBody = cocos2d::PhysicsBody::createCircle(reward->getContentSize().width / 2);

	auto random = CCRANDOM_0_1();

	auto topPosition = random * (visibleSize.height) + reward->getContentSize().height / 2;

	rewardBody->setDynamic(false);
	rewardBody->setCollisionBitmask(DOLLAR_COLLISION_BITMASK);
	rewardBody->setContactTestBitmask(true);
	reward->setPhysicsBody(rewardBody);

	reward->setPosition(cocos2d::Point(visibleSize.width + reward->getContentSize().width, topPosition));

	layer->addChild(reward);

	auto moveAction = cocos2d::MoveBy::create(DOLLAR_MOVEMENT_SPEED * visibleSize.width - level, cocos2d::Point(-visibleSize.width * 2.5, 0));

	reward->runAction(moveAction);

	return reward;
}