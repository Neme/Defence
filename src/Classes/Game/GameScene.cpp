#include "GameScene.h"
#include "Level/RandomTreeLevel.h"
#include "GameManager.h"

using namespace cocos2d;

//-----------------------------------------------------------//
bool GameScene::init()
{
	if (!Scene::init())
		return false;

	auto lvlMgr = GameManager::get<LevelManager>();
	

	m_backgroundLayer = util::create<BackgroundLayer>();
	m_gameLayer = util::create<GameLayer>();
	m_guiLayer = util::create<GUILayer>();


	this->addChild(m_backgroundLayer);
	this->addChild(m_gameLayer);
	this->addChild(m_guiLayer);

	lvlMgr->setGameLayer(*m_gameLayer);
	lvlMgr->spawnLevel<RandomTreeLevel>();


    return true;
}
//-----------------------------------------------------------//


