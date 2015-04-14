#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include <map>
#include "cocos2d.h"
#include "Const.h"
#include "../Level/LevelManager.h"

class GameLayer : public cocos2d::Layer
{
public:
	GameLayer();

	void update(float delta) override;
	void pulse(float delta);

	//void spawnPacket(Tower& tower);
	void setGameLevel(Level& level);
	

private:

	//Events
	cocos2d::Vec2 m_scaleAnchorPoint;
	void initEvents();

};

#endif // __GAME_LAYER_H__
