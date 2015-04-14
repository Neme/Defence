#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include "Util/Util.h"

class BackgroundLayer : public cocos2d::Layer
{
public:
	BackgroundLayer();

private:
	cocos2d::Sprite* m_backgroundSprite;
};

#endif // __BACKGROUND_LAYER_H__
