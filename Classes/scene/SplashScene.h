#ifndef _SPLASH_SCENE_H_
#define _SPLASH_SCENE_H_

#include "cocos2d.h"
#include "Definitions.h"
#include "MainMenuScene.h"

class SplashScene : public cocos2d::Scene
{
private:
	void goToMainMenu(float displayTime);

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(SplashScene);
};

#endif
