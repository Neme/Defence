#include "GameScene.h"
#include "Level/RandomTreeLevel.h"

USING_NS_CC;

//-----------------------------------------------------------//
bool GameScene::init()
{
	if (!Scene::init())
		return false;

	m_backgroundLayer = util::create<BackgroundLayer>();
	m_gameLayer = util::create<GameLayer>();
	m_guiLayer = util::create<GUILayer>();


	this->addChild(m_backgroundLayer);
	this->addChild(m_gameLayer);
	this->addChild(m_guiLayer);

    return true;
}
//-----------------------------------------------------------//


