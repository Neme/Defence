#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <memory>
#include "cocos2d.h"
#include "Level/LevelManager.h"
#include "Layer/BackgroundLayer.h"
#include "Layer/GameLayer.h"
#include "Layer/GUILayer.h"
#include "Util/Util.h"


class GameScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(GameScene);
    virtual bool init() override;

private:
	//Layers
	BackgroundLayer* m_backgroundLayer;
	GameLayer* m_gameLayer;
	GUILayer* m_guiLayer;


};

#endif // __GAME_SCENE_H__
