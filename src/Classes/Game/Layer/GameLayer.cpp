#include <functional>
#include <map>
#include "ui/UIButton.h"
#include "GameLayer.h"
#include "GUILayer.h"
#include "../Entity/Tower.h"
#include "../Entity/Edge.h"
#include "../Entity/Packet.h"
#include "../GameManager.h"


using namespace cocos2d;


//---------------------------------------------------------------------//
GameLayer::GameLayer()
{

	if (!Layer::init())
		return;

	//Center screen so the main tower will be at (0,0)
	auto ws = Director::getInstance()->getWinSize();
	this->setPosition({ ws.width / 2, ws.height / 2 });
	this->setAnchorPoint({ 0, 0 });
	this->scheduleUpdate();

	//Init events
	this->initEvents();

	//Init schedules
	this->schedule(std::bind(&GameLayer::pulse, this, std::placeholders::_1), 0.1f, "game_pulse");


}
//---------------------------------------------------------------------//
void GameLayer::initEvents()
{
	//Events
	//Touch -> Camera
	auto cameraListenerTouch = EventListenerTouchAllAtOnce::create();
	cameraListenerTouch->onTouchesMoved = [this](const std::vector<Touch*>& touches, Event  *event) {
		if (touches.size() == 1) {
			auto delta = touches[0]->getDelta();
			this->setPosition(this->getPosition() + delta);

			//Hide tower update gui
			auto gui = GameManager::get<LayerManager>()->getLayer<GUILayer>();
			gui->cameraMoved();
		}
		else if (touches.size() == 2) {
			auto deltaNew = touches[0]->getLocation() - touches[1]->getLocation();
			auto deltaOld = touches[0]->getPreviousLocation() - touches[1]->getPreviousLocation();
			auto scale = (deltaOld - deltaNew).length() * (deltaOld.length()>deltaNew.length() ? -1 : 1);

			if ((this->getScale() < 10.0f && scale > 0) || (this->getScale() > 0.1f && scale < 0))
				this->setScale(this->getScale() + this->getScale()*scale /720);
		}
	};

	//Mouse -> Camera
	auto cameraListenerMouse = EventListenerMouse::create();
	cameraListenerMouse->onMouseScroll = [this](Event *event){
		auto scrollY = static_cast<EventMouse*>(event)->getScrollY();

		const float maxScale = 3.0f;
		const float minScale = 0.1f;

		auto newScale = this->getScale() - scrollY / 10.0f;

		if (newScale >= minScale && newScale <= maxScale)
			this->setScale(newScale);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(cameraListenerTouch, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(cameraListenerMouse, this);

}
//---------------------------------------------------------------------//
void GameLayer::pulse(float delta)
{
	auto towers = GameManager::get<EntityManager>()->getEntitiesByGroup<Tower>();
	for (auto& tower : towers) {
		tower->pulse(delta);
	}
}
//---------------------------------------------------------------------//

