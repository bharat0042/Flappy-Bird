#include "GameOverScene.h"

cocos2d::Scene* GameOverScene::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = cocos2d::Sprite::create("images/Background.png");
	backgroundSprite->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	auto retryItem = cocos2d::MenuItemImage::create("images/RetryButton.png", "images/RetryButtonClicked.png", CC_CALLBACK_1(GameOverScene::goToGameScene, this));
	retryItem->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3));

	auto mainMenuItem = cocos2d::MenuItemImage::create("images/MainMenuButton.png", "images/MainMenuButtonClicked.png", CC_CALLBACK_1(GameOverScene::goToMainMenuScene, this));

	mainMenuItem->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4));

	auto menu = cocos2d::Menu::create(retryItem, mainMenuItem, NULL);
	menu->setPosition(cocos2d::Point::ZERO);

	this->addChild(menu);

	return true;
}

void GameOverScene::goToMainMenuScene(cocos2d::Ref *sender)
{
	auto scene = MainMenuScene::createScene();

	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::goToGameScene(cocos2d::Ref *sender)
{
	auto scene = GameScene::createScene();

	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(TRANSITION_TIME, scene));
}