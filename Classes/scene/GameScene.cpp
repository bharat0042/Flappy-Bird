#include "GameScene.h"

cocos2d::Scene* GameScene::createScene()
{
	auto scene = cocos2d::Scene::createWithPhysics();
 
	scene->getPhysicsWorld()->setGravity(cocos2d::Vect(0, 0));

	auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	bird = new Bird(this);
	score = 0;
	level = 1;

	auto backgroundSprite = cocos2d::Sprite::create("images/Background.png");
	backgroundSprite->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	auto edgeBody = cocos2d::PhysicsBody::createEdgeBox(visibleSize, cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	std::string scoreStr = outScore + std::to_string(score);

	scoreLabel = cocos2d::Label::createWithTTF(scoreStr.c_str(), "fonts/TelemarinesBold.ttf", 30);

	scoreLabel->setColor(cocos2d::Color3B::WHITE);
	scoreLabel->setPosition(cocos2d::Point(visibleSize.width - scoreLabel->getContentSize().width - 100, visibleSize.height - scoreLabel->getContentSize().height));

	this->addChild(scoreLabel, 10000);

	this->schedule(cocos2d::SEL_SCHEDULE(&GameScene::spawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);

	this->schedule(cocos2d::SEL_SCHEDULE(&GameScene::spawnReward), DOLLAR_SPAWN_FREQUENCY * visibleSize.width);

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto keyboardlistener = cocos2d::EventListenerKeyboard::create();
	keyboardlistener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyBegin, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

	this->scheduleUpdate();

	showLevel(level);

	return true;
}

void GameScene::spawnPipe(float displayTime)
{
	pipe.spawnPipe(this, level);
}

void GameScene::spawnReward(float displayTime)
{
	tmpReward = reward.spawnReward(this, level);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	static unsigned int pointPassed = 0;

	cocos2d::PhysicsBody* a = contact.getShapeA()->getBody();
	cocos2d::PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == BIRD_COLLISION_BITMASK && b->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK) ||
		(b->getCollisionBitmask() == BIRD_COLLISION_BITMASK && a->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK))
	{
		auto scene = GameOverScene::createScene();
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(TRANSITION_TIME, scene, cocos2d::Color3B(40, 47, 60)));

		AudioManager::playSoundEffect("audio/smash.mp3", 0.5);

		return true;
	}
	else if ((a->getCollisionBitmask() == BIRD_COLLISION_BITMASK && b->getCollisionBitmask() == POINT_COLLISION_BITMASK) ||
		(b->getCollisionBitmask() == BIRD_COLLISION_BITMASK && a->getCollisionBitmask() == POINT_COLLISION_BITMASK))
	{
		score += POINT_PASS_SCORE;
		pointPassed++;

		if (score % 100 == 0)
		{
			level++;
			showLevel(level);
		}

		std::string scoreStr = outScore + std::to_string(score);
		scoreLabel->setString(scoreStr.c_str());

		AudioManager::playSoundEffect("audio/point.mp3", 0.5);

		return false;
	}
	else if ((a->getCollisionBitmask() == BIRD_COLLISION_BITMASK && b->getCollisionBitmask() == DOLLAR_COLLISION_BITMASK) ||
		(b->getCollisionBitmask() == BIRD_COLLISION_BITMASK && a->getCollisionBitmask() == DOLLAR_COLLISION_BITMASK))
	{
		score += DOLLAR_SCORE;

		if (score % 100 == 0)
		{
			level++;
			showLevel(level);
		}

		std::string scoreStr = outScore + std::to_string(score);
		scoreLabel->setString(scoreStr.c_str());

		AudioManager::playSoundEffect("audio/dollar.mp3", 0.5);

		this->removeChild(tmpReward, true);

		return false;
	}
}

bool GameScene::onKeyBegin(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		bird->raise();
		this->scheduleOnce(cocos2d::SEL_SCHEDULE(&GameScene::birdFall), BIRD_FLY_DURATION);
	}

	return true;
}

void GameScene::birdFall(float dt)
{
	bird->fall();
}

void GameScene::update(float dt)
{
	bird->fly();
}

void GameScene::showLevel(int level)
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto levelLabel = cocos2d::Label::createWithTTF("LEVEL " + std::to_string(level), "fonts/TelemarinesBold.ttf", 50);
	levelLabel->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + levelLabel->getContentSize().height));

	this->addChild(levelLabel, 10000);

	auto fadeIn = cocos2d::FadeIn::create(1.0f);
	auto fadeOut = cocos2d::FadeOut::create(1.0f);

	auto sequence = cocos2d::Sequence::create(fadeIn, fadeOut, nullptr);

	levelLabel->runAction(sequence);
}