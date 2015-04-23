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
	auto layerMgr = GameManager::get<LayerManager>();
	

	m_backgroundLayer = util::create<BackgroundLayer>();
	m_gameLayer = util::create<GameLayer>();
	m_guiLayer = util::create<GUILayer>();

	layerMgr->setLayer<BackgroundLayer>(m_backgroundLayer);
	layerMgr->setLayer<GameLayer>(m_gameLayer);
	layerMgr->setLayer<GUILayer>(m_guiLayer);


	this->addChild(m_backgroundLayer);
	this->addChild(m_gameLayer);
	this->addChild(m_guiLayer);

	
	lvlMgr->spawnLevel<RandomTreeLevel>();


    return true;
}
//-----------------------------------------------------------//


