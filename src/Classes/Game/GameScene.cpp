#include "GameScene.h"
#include "Level/RandomTreeLevel.h"
#include "GameManager.h"

using namespace cocos2d;

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

	auto lvlMgr = GameManager::get<LevelManager>();
	lvlMgr->spawnLevel<RandomTreeLevel>();
	m_gameLayer->setGameLevel(*lvlMgr->getCurrentLevel<RandomTreeLevel>());

    return true;
}
//-----------------------------------------------------------//


