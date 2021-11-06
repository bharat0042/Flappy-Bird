#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

#include "MainMenuScene.h"
#include "Definitions.h"

class GameOverScene : public cocos2d::Layer
{
private:
	void goToMainMenuScene(cocos2d::Ref *sender);

	void goToGameScene(cocos2d::Ref *sender);

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameOverScene);
};


#endif