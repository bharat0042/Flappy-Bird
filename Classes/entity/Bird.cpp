#include "Bird.h"

Bird::Bird(cocos2d::Layer *layer) : 
	visibleSize{ cocos2d::Director::getInstance()->getVisibleSize() },
	origin{ cocos2d::Director::getInstance()->getVisibleOrigin() },
	isGoingUp{ false }
{
	flappyBird = cocos2d::Sprite::create("images/Bird.png");
	flappyBird->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	flappyBird->setScale(0.5);

	auto flappyBirdBody = cocos2d::PhysicsBody::createCircle(flappyBird->getContentSize().width / 2);
	flappyBirdBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	flappyBirdBody->setContactTestBitmask(true);
	flappyBird->setPhysicsBody(flappyBirdBody);

	layer->addChild(flappyBird, 100);
}

void Bird::fly()
{
	if (isGoingUp == true)
	{
		flappyBird->setPositionX(visibleSize.width / 2 + origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY() + BIRD_FLYING_SPEED * visibleSize.height);
	}
	else
	{
		flappyBird->setPositionX(visibleSize.width / 2 + origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY() - BIRD_FALLING_SPEED * visibleSize.height);
	}
}

void Bird::raise()
{
	isGoingUp = true;
}

void Bird::fall()
{
	isGoingUp = false;
}