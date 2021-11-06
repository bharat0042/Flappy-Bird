#ifndef __MAINMENU_SCENE_H__
#define  __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Definitions.h"
#include "utils/AudioManager.h"
#include "GameScene.h"

class MainMenuScene : public cocos2d::Scene
{
private:
	void goToGame();

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MainMenuScene);
};

#endif
