#include "MainMenuScene.h"

void MainMenuScene::goToGame()
{
    auto scene = GameScene::createScene();

    cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(TRANSITION_TIME, scene, cocos2d::Color3B(40, 47, 60)));
}

cocos2d::Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

bool MainMenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = cocos2d::Sprite::create("images/Background.png");
    backgroundSprite->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(backgroundSprite);

    auto titleSprite = cocos2d::Sprite::create("images/Title.png");
    titleSprite->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + titleSprite->getContentSize().height));

    this->addChild(titleSprite);

    auto playItem = cocos2d::MenuItemImage::create("images/PlayButton.png", "images/PlayButtonClicked.png", CC_CALLBACK_0(MainMenuScene::goToGame, this));
    playItem->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    auto menu = cocos2d::Menu::create(playItem, nullptr);
    menu->setPosition(cocos2d::Point::ZERO);

    this->addChild(menu);

	auto soundCheckBox = cocos2d::ui::CheckBox::create("images/SoundButton.png", "images/SoundButtonChecked.png");
	soundCheckBox->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - playItem->getContentSize().height * 1.4f));

	soundCheckBox->setSelected(!AudioManager::getSoundState());

	this->addChild(soundCheckBox);

	soundCheckBox->addEventListener([](Ref *sender, cocos2d::ui::CheckBox::EventType type)
	{
		switch (type)
		{
			case cocos2d::ui::CheckBox::EventType::SELECTED:
				AudioManager::muteSounds();
				break;
			case cocos2d::ui::CheckBox::EventType::UNSELECTED:
				AudioManager::unmuteSounds();
				break;
			default:
				break;
		}});
	return true;
}
