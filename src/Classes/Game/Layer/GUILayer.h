#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"
#include "GameLayer.h"
#include "../Entity/Tower.h"
#include "../Level/LevelManager.h"
#include "ui/UIButton.h"
#include "ui/UILayout.h"
#include "ui/UIText.h"


class GUILayer : public cocos2d::Layer
{
public:
	GUILayer();


	void showTowerUpgrade(Tower* tower);
	void update(float delta) override;
	void cameraMoved();
private:
	void createDebugUI();


	//Tower Upgrade
	cocos2d::ui::Layout* m_towerUpgradeLayout;
	Tower* m_selectedTower{ nullptr };
	void createTowerUpdateWindow();
	void toggleTowerUpdateWindow();


};

#endif // __HUD_LAYER_H__
