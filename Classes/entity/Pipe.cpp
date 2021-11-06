#include "Pipe.h"

Pipe::Pipe() :
	visibleSize{ cocos2d::Director::getInstance()->getVisibleSize() },
	origin{ cocos2d::Director::getInstance()->getVisibleOrigin() }
{

}

void Pipe::spawnPipe(cocos2d::Layer *layer, unsigned int level)
{
	auto topPipe = cocos2d::Sprite::create("images/Pipe.png");
	auto bottomPipe = cocos2d::Sprite::create("images/Pipe.png");

	auto topPipeBody = cocos2d::PhysicsBody::createBox(topPipe->getContentSize());
	auto bottomPipeBody = cocos2d::PhysicsBody::createBox(bottomPipe->getContentSize());

	auto random = CCRANDOM_0_1();

	if (random < LOWER_SCREEN_PIPE_THRESHOLD)
	{
		random = LOWER_SCREEN_PIPE_THRESHOLD;
	}
	else if (random > UPPER_SCREEN_PIPE_THRESHOLD)
	{
		random = UPPER_SCREEN_PIPE_THRESHOLD;
	}

	auto topPipePosition = random * (visibleSize.height) + topPipe->getContentSize().height / 2;

	topPipeBody->setDynamic(false);
	bottomPipeBody->setDynamic(false);

	topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);

	topPipeBody->setContactTestBitmask(true);
	bottomPipeBody->setContactTestBitmask(true);

	topPipe->setPhysicsBody(topPipeBody);
	bottomPipe->setPhysicsBody(bottomPipeBody);

	topPipe->setPosition(cocos2d::Point(visibleSize.width + topPipe->getContentSize().width, topPipePosition));
	bottomPipe->setPosition(cocos2d::Point(topPipe->getPositionX(), topPipe->getPositionY() - topPipe->getContentSize().height - cocos2d::Sprite::create("images/Bird.png")->getContentSize().height));

	layer->addChild(topPipe);
	layer->addChild(bottomPipe);

	auto topPipeAction = cocos2d::MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width - level, cocos2d::Point(-visibleSize.width * 2.5, 0));
	auto bottomPipeAction = cocos2d::MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width - level, cocos2d::Point(-visibleSize.width * 2.5, 0));

	topPipe->runAction(topPipeAction);
	bottomPipe->runAction(bottomPipeAction);

	auto pointNode = cocos2d::Node::create();
	auto pointBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(1, cocos2d::Sprite::create("images/Bird.png")->getContentSize().height));
	pointBody->setDynamic(false);
	pointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
	pointBody->setContactTestBitmask(true);

	pointNode->setPhysicsBody(pointBody);
	pointNode->setPosition(cocos2d::Point(topPipe->getPositionX(), topPipe->getPositionY() - topPipe->getContentSize().height / 2 - cocos2d::Sprite::create("images/Bird.png")->getContentSize().height / 2));

	layer->addChild(pointNode);

	auto pointNodeAction = cocos2d::MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width - level, cocos2d::Point(-visibleSize.width * 2.5, 0));
	pointNode->runAction(pointNodeAction);
}