#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "entity/Bird.h"
#include "entity/Pipe.h"
#include "entity/Reward.h"

#include "utils/AudioManager.h"

#include "scene/GameOverScene.h"

#include "Definitions.h"

class GameScene : public cocos2d::Layer
{
private:
	cocos2d::PhysicsWorld *sceneWorld;
	Pipe pipe;
	Reward reward;
	Bird *bird;
	int score;
	std::string outScore = "Score :";
	unsigned int level;
	cocos2d::Label *scoreLabel;
	cocos2d::Sprite *tmpReward;

	void setPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
	void spawnPipe(float displayTime);
	void spawnReward(float displayTime);
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	bool onKeyBegin(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void birdFall(float dt);
	void update(float dt);
	void showLevel(int level);

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(GameScene);
};

#endif