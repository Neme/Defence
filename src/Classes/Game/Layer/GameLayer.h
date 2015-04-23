#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__


#include "cocos2d.h"
#include "Const.h"

class Tower;

class GameLayer : public cocos2d::Layer
{
public:
	GameLayer();
	void pulse(float delta);

private:

	//Events
	cocos2d::Vec2 m_scaleAnchorPoint;
	void initEvents();

};

#endif // __GAME_LAYER_H__
