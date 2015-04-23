#include "Packet.h"
#include "Const.h"
#include "Tower.h"
#include "Packet.h"
#include "../Layer/GUILayer.h"

#include "../GameManager.h"


using namespace cocos2d;

//---------------------------------------------------------------------//
Tower::Tower()
{
	static int s_towerId = 1;
	m_towerUuid = s_towerId++;

}
//---------------------------------------------------------------------//
Tower* Tower::getRandomChildTower()
{
	int maxPos = m_childrenTowers.size()-1;

	//if there is no child
	if (maxPos < 0)
		return nullptr;

	return m_childrenTowers.at(round(maxPos*rand_0_1()));
}
//---------------------------------------------------------------------//
Tower* Tower::getRandomNeighborTower()
{
	std::vector<Tower*> vulnerabeChildren;
	for (auto neightbor : this->getNeightborTowers()) {
		if (neightbor->hasVulnerableNeighborTower(this->getTowerType(), *this)) {
			vulnerabeChildren.push_back(neightbor);
		}
	}


	int maxPos = vulnerabeChildren.size() - 1;

	//there is no child
	if (maxPos < 0)
		return nullptr;

	return vulnerabeChildren.at(round(maxPos*rand_0_1()));
}
//---------------------------------------------------------------------//
Tower* Tower::getRandomNextTower(const Tower& lastTower)
{
	for (int i = 0; i < 10; i++) {
		auto tower = getRandomNeighborTower();
		if (tower != &lastTower) {
			return tower;
		}
	}

	return nullptr;
}
//---------------------------------------------------------------------//
void Tower::setTowerType(TowerType type)
{
	m_towerType = type;

	Color3B towerColor = { 10, 10, 10 };

	switch (type)
	{
	case TowerType::TYPE_NEUTRAL:		
		towerColor = { 10, 10, 10 }; 
		break;
	case TowerType::TYPE_ALLY:		
		towerColor = { 38, 107, 36 }; break;
	case TowerType::TYPE_ENEMY:	
		towerColor = { 149, 56, 102 };	 
		break;
	default:
		break;
	}

	this->setColor(towerColor);
}
//---------------------------------------------------------------------//
void Tower::setTowerJob(TowerJob job)
{
	m_towerJob = job;

	switch (job)
	{
	case TowerJob::JOB_NORMAL:
		break;
	case TowerJob::JOB_SPAWNER:
		this->setScale(1.5f);
		break;
	default:
		break;
	}
}
//---------------------------------------------------------------------//
bool Tower::receivePacket(Packet& packet)
{
	if (m_towerJob == TowerJob::JOB_SPAWNER)
		return true;


	bool returnedValue = false;


	if ((int)packet.getPacketType() != (int)m_towerType) {
		m_health--;
		returnedValue = true;

		if (m_health == 0) {
			m_health = 5;

			this->setTowerType(static_cast<TowerType>(packet.getPacketType()));
		}


	} else {
		if (m_health < 5) {
			m_health++;
			returnedValue =  true;
		}
	}

	this->setScale(0.5f + 0.1f*m_health);


	return returnedValue;
}
//---------------------------------------------------------------------//
bool Tower::hasVulnerableNeighborTower(TowerType friendType, Tower& sender)
{
	if (this->getTowerType() != friendType)
		return true;

	for (auto neightbor : this->getNeightborTowers()) {
		if (neightbor == &sender)
			continue;

		if (neightbor->hasVulnerableNeighborTower(friendType, *this))
			return true;
	}

	return false;
}
//---------------------------------------------------------------------//
std::vector<Tower*> Tower::getNeightborTowers()
{
	std::vector<Tower*> towers = m_childrenTowers;

	if (m_parentTower != nullptr)
		towers.push_back(m_parentTower);


	return towers;
}
//---------------------------------------------------------------------//
void Tower::initEventListener()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
		if (rect.containsPoint(this->convertTouchToNodeSpace(touch))) {
			return true;
		}
		return false;
	};
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		//Get GUI layer
		auto gui = GameManager::get<LayerManager>()->getLayer<GUILayer>();
		if (gui == nullptr)
			return;

		gui->showTowerUpgrade(*this);
	};


	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
//---------------------------------------------------------------------//
void Tower::pulse(float delta)
{
	m_pulseTimeDelta += delta;

	if (m_pulseTime <= m_pulseTimeDelta) {
		m_pulseTimeDelta = 0;

		if (this->getTowerJob() == TowerJob::JOB_SPAWNER) {
			auto entityMgr = GameManager::get<EntityManager>();
			auto packet = entityMgr->addEntity<Packet>(*this, *this->getRandomNeighborTower());
			packet->setPosition(this->getPosition());
		}

	}
}
//---------------------------------------------------------------------//
bool Tower::init()
{

	if (!CocosBase::init())
		return false;


	this->setTowerType(TowerType::TYPE_NEUTRAL);
	this->setTowerJob(TowerJob::JOB_NORMAL);
	this->setTextureRect({ 0, 0, 80, 80 });
	this->setTag((int)EntityTag::Tower);

	//Init shader
	if (!ShaderCache::getInstance()->getGLProgram("shader_tower")) {
		auto shader = GLProgram::createWithFilenames("shader/tower.vert", "shader/tower.frag");
		shader->link();
		shader->updateUniforms();
		ShaderCache::getInstance()->addGLProgram(shader, "shader_tower");
	}

	auto shader = ShaderCache::getInstance()->getGLProgram("shader_tower");

	auto glProgramState = GLProgramState::create(shader);
	glProgramState->setUniformVec2("towerSize", this->getContentSize());
	glProgramState->setUniformFloat("pulseTime", rand_0_1() * 15.0f + 10.0f);


	this->setGLProgram(shader);
	this->setGLProgramState(glProgramState);


	this->initEventListener();

	return true;
}
//---------------------------------------------------------------------//
Edge* Tower::getEdge(const Tower& neighbor)
{
	auto edges = GameManager::get<EntityManager>()->getEntitiesByGroup<Edge>();

	for (auto& edge : edges) {
		if (edge->getStartTower() == this && edge->getDestTower() == &neighbor ||
			edge->getDestTower() == this && edge->getStartTower() == &neighbor) {
			return edge;
		}
	}

	return nullptr;
}
//---------------------------------------------------------------------//
Edge* Tower::getRandomNextEdge(const Tower& lastTower)
{
	return this->getEdge(*this->getRandomNextTower(lastTower));
}
//---------------------------------------------------------------------//
Edge* Tower::getRandomNeighborEdge()
{
	return this->getEdge(*this->getRandomNeighborTower());
}

//-----------------------------------------------------------//


