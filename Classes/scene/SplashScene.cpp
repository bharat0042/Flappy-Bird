#include "SplashScene.h"

void SplashScene::goToMainMenu(float displayTime) 
{
	auto scene = MainMenuScene::createScene();

	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(TRANSITION_TIME, scene, cocos2d::Color3B(40, 47, 60)));
}

cocos2d::Scene* SplashScene::createScene()
{
	return SplashScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SplashScene.cpp\n");
}

bool SplashScene::init() 
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	this->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::goToMainMenu), DISPLAY_TIME_SPLASH_SCENE);

	auto backgroundSprite = cocos2d::Sprite::create("images/SplashScreen.png");
	backgroundSprite->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	return true;
}