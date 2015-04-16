#include "GUILayer.h"
#include <functional>
#include <array>
#include <tuple>
#include "../GameManager.h"
#include "../Level/RandomTreeLevel.h"

using namespace cocos2d;


//---------------------------------------------------------------------//
GUILayer::GUILayer()
{
	if (!Layer::init())
		return;

	this->setTag((int)LayerTags::LAYER_GUI);

	this->createDebugUI();
	this->scheduleUpdate();

	this->createTowerUpdateWindow();
}
//---------------------------------------------------------------------//
void GUILayer::createDebugUI()
{
	auto ws = Director::getInstance()->getWinSize();

	//Debug layer
	auto debugLayer = Layer::create();
	debugLayer->setVisible(false);
	this->addChild(debugLayer);

	//Debug layer toggle button
	auto toggleDebugBtn = ui::Button::create("btn_debug.png");
	toggleDebugBtn->setPosition({50, 50});
	toggleDebugBtn->addTouchEventListener(
		[debugLayer](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED) {
			debugLayer->setVisible(!debugLayer->isVisible());
		}
	});
	this->addChild(toggleDebugBtn);

	auto level = GameManager::get<LevelManager>()->getCurrentLevel<RandomTreeLevel>();

	//Button vector
	//Structure:
	// - ImgName
	// - ImgHoverName
	// - Event
	const std::vector<std::tuple<std::string, std::string, std::function<void(Ref*, ui::Widget::TouchEventType)>>> buttonsData = {

		//New button
		std::make_tuple(
			"btn_new.png","btn_new.png",
			[this](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					//level->spawnTowers();
				}
			}
		),

		//Not set jet
		std::make_tuple(
			"btn_new.png", "btn_new.png",
			[this](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					//m_game->spawnTowers();
				}
			}
		),
		
		//increase depth
		std::make_tuple(
			"btn_plus.png","btn_plus.png",
			[&level](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					level->setTowerNodeDepth(level->getTowerNodeDepth() + 1);
				}
			}
		),

		//decrease depth
		std::make_tuple(
			"btn_minus.png","btn_minus.png",
			[&level](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					level->setTowerNodeDepth(level->getTowerNodeDepth() - 1);
				}
			}
		),


		//increase min child count
		std::make_tuple(
			"btn_plus.png", "btn_plus.png",
			[&level](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					level->setMinChildCount(level->getMinChildCount() + 1);
				}
			}
		),

		//decrease min child count
		std::make_tuple(
			"btn_minus.png", "btn_minus.png",
			[&level](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					level->setMinChildCount(level->getMinChildCount() - 1);
				}
			}
		),

		//increase max child count
		std::make_tuple(
			"btn_plus.png", "btn_plus.png",
			[&level](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					level->setMaxChildCount(level->getMaxChildCount() + 1);
				}
			}
		),

		//decrease max child count
		std::make_tuple(
			"btn_minus.png", "btn_minus.png",
			[&level](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					level->setMaxChildCount(level->getMaxChildCount() - 1);
				}
			}
		),

		//increase min edge length
		std::make_tuple(
			"btn_plus.png", "btn_plus.png",
			[&level](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					level->setMinEdgeLength(level->getMinEdgeLength() + 10);
				}
			}
		),

		//decrease min edge length
		std::make_tuple(
			"btn_minus.png", "btn_minus.png",
			[&level](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					level->setMinEdgeLength(level->getMinEdgeLength() - 10);
				}
			}
		),

		//increase max edge length
		std::make_tuple(
			"btn_plus.png", "btn_plus.png",
			[&level](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					level->setMaxEdgeLength(level->getMaxEdgeLength() + 10);
				}
			}
		),

		//decrease max edge length
		std::make_tuple(
			"btn_minus.png", "btn_minus.png",
			[&level](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					level->setMaxEdgeLength(level->getMaxEdgeLength() - 10);
				}
			}
		),
	};

	//Create buttons from button vector
	auto size = Size{ 
		ws.height / 15,
		ws.height / 15
	};

	int index = 0;
	for (auto data : buttonsData){
		auto btn = ui::Button::create(std::get<0>(data), std::get<1>(data));
		btn->setPressedActionEnabled(true);
		btn->setPosition({100.0f+ (size.width * (index % 2)), ws.height - 75.0f - size.height*(index / 2) });
		btn->addTouchEventListener(std::get<2>(data));
		btn->setScale(size.width / 50.0f, size.height / 50.0f);

		debugLayer->addChild(btn);
		index++;
	}

}
//---------------------------------------------------------------------//
void GUILayer::showTowerUpgrade(Tower* tower)
{
	auto ws = Director::getInstance()->getWinSize();

	m_selectedTower = tower;
	auto localPos = m_selectedTower->getParent()->convertToWorldSpace(m_selectedTower->getPosition());


	//Flip update window so it's always in screen
	if (localPos.x > ws.width / 2) {
		m_towerUpgradeLayout->setScaleX(-1.0f);
	}
	else {
		m_towerUpgradeLayout->setScaleX(1.0f);
	}

	
	this->toggleTowerUpdateWindow();

}
//---------------------------------------------------------------------//
void GUILayer::update(float delta)
{
	if (m_selectedTower != nullptr) {
		auto localPos = m_selectedTower->getParent()->convertToWorldSpace(m_selectedTower->getPosition());
		localPos.y -= m_towerUpgradeLayout->getContentSize().height / 2.0f;
		m_towerUpgradeLayout->setPosition(localPos);
	}
}
//---------------------------------------------------------------------//
void GUILayer::createTowerUpdateWindow()
{
	auto ws = Director::getInstance()->getWinSize();

	m_towerUpgradeLayout = ui::Layout::create();
	m_towerUpgradeLayout->setBackGroundColorType(ui::Layout::BackGroundColorType::NONE);
	m_towerUpgradeLayout->setContentSize({ ws.width * 0.4f, ws.width * 0.1f });
	m_towerUpgradeLayout->setVisible(false);
	this->addChild(m_towerUpgradeLayout);

	//Create background arrow
	auto background = DrawNode::create();
	background->clear();
	auto size = m_towerUpgradeLayout->getContentSize();
	std::vector<cocos2d::Vec2> points{
		{ 0, size.height / 2 },
		{ size.width * 0.1f, 0 },
		{ size.width, 0 },
		{ size.width, size.height },
		{ size.width * 0.1f, size.height },
	};

	background->drawPolygon(
		&points[0],
		points.size(),
		{ 0.2f, 0.2f, 0.2f, 0.6f },
		1,
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	);

	m_towerUpgradeLayout->addChild(background);


	auto xOffset = m_towerUpgradeLayout->getSize().width * 0.21f;
	for (int i = 0; i < 4; i++) {
		auto btn = ui::Button::create("img/btn_raw.png", "img/btn_raw_d.png");
		btn->setScale((m_towerUpgradeLayout->getSize().height * 0.8f) / btn->getSize().height);
		btn->setColor({ 10, 10, 10 });
		btn->setPressedActionEnabled(true);

		btn->setPosition({
			xOffset + i*(m_towerUpgradeLayout->getSize().height * 0.8f + 10),
			m_towerUpgradeLayout->getContentSize().height*0.5f
		});

		btn->addTouchEventListener(
			[this](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					m_selectedTower->setPulseTime(m_selectedTower->getPulseTime() * 0.5f);
				}
			}
		);

		m_towerUpgradeLayout->addChild(btn);
	}

}
//---------------------------------------------------------------------//
void GUILayer::cameraMoved()
{
	if (m_selectedTower != nullptr)
		m_selectedTower = nullptr;

	if (m_towerUpgradeLayout->isVisible())
		m_towerUpgradeLayout->setVisible(false);
}
//---------------------------------------------------------------------//
void GUILayer::toggleTowerUpdateWindow()
{
	m_towerUpgradeLayout->setVisible(!m_towerUpgradeLayout->isVisible());
}
