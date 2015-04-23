#include "Packet.h"
#include "Const.h"
#include "Tower.h"
#include "Packet.h"
#include "../Layer/GUILayer.h"

#include "../GameManager.h"


using namespace cocos2d;

_constexpr std::map<TowerType, cocos2d::Color3B> cTowerColors{
	{ TowerType::Neutral, { 10, 10, 10 } },
	{ TowerType::Ally, { 38, 107, 36 } },
	{ TowerType::Enemy, { 149, 56, 102 } }
};


//---------------------------------------------------------------------//
Tower::Tower()
{
	this->setTowerType(TowerType::Neutral);
	m_gatherTime = rand_0_1() * 10.0f + 10.0f;
}
//---------------------------------------------------------------------//
void Tower::setTowerType(TowerType type)
{
	m_towerType = type;
	this->setColor(cTowerColors.at(type));
}
//---------------------------------------------------------------------//
void Tower::setTowerJob(TowerJob job)
{
	m_towerJob = job;

	//Spawn towers are bigger
	if (job == TowerJob::Spawner)
		this->setScale(1.7f);

}
//---------------------------------------------------------------------//
void Tower::receivePacket(Packet& packet)
{
	auto entityMgr = GameManager::get<EntityManager>();

	//Spawner's don't count
	if (m_towerJob == TowerJob::Spawner) {
		entityMgr->removeEntity<Packet>(packet);
		return;
	}
		

	//Increase/decrease health
	((int)packet.getPacketType() != (int)m_towerType) ? m_health -= packet : m_health += packet;

	//Reset health, if tower type has changed
	if (m_health == 0) {
		m_health.reset();
		this->setTowerType(static_cast<TowerType>(packet.getPacketType()));
	}

	if ((int)packet.getPacketType() != (int)m_towerType) {
		entityMgr->removeEntity<Packet>(packet);
	}

	//The more health a tower has the bigger it is
	this->setScale(0.5f + m_health.getHealthPercentage() / 200.0f);
}
//---------------------------------------------------------------------//
bool Tower::init()
{

	if (!CocosBase::init())
		return false;


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
	glProgramState->setUniformFloat("pulseTime", m_pulseTime);
	glProgramState->setUniformInt("drawMode", (int)m_drawMode);


	this->setGLProgram(shader);
	this->setGLProgramState(glProgramState);


	this->initEventListener();

	return true;
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

		if (m_canGather) {
			this->doGather();
			return;
		}

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
	m_gatherTimeDelta += delta;

	//Pulse
	if (m_pulseTime <= m_pulseTimeDelta) {
		m_pulseTimeDelta = 0;

		if (this->getTowerJob() == TowerJob::Spawner) {
			auto entityMgr = GameManager::get<EntityManager>();
			auto packet = entityMgr->addEntity<Packet>(*this, *this->getRandomNeighborTower());
			packet->setPosition(this->getPosition());
		}
	}

	//Gather
	if (m_gatherTime <= m_gatherTimeDelta && !m_canGather) {
		m_gatherTimeDelta = 0;

		if (this->getTowerType() != TowerType::Neutral) {
			m_canGather = true;
			this->setDrawMode(TowerDrawMode::Gather);
		}
	}

}
//---------------------------------------------------------------------//
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
Tower* Tower::getRandomChildTower()
{
	int maxPos = m_childrenTowers.size() - 1;

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
void Tower::setPulseTime(float time)
{
	m_pulseTime = time; 
	this->getGLProgramState()->setUniformFloat("pulseTime", m_pulseTime);
}
//---------------------------------------------------------------------//
void Tower::setDrawMode(TowerDrawMode drawMode)
{
	m_drawMode = drawMode;
	this->getGLProgramState()->setUniformInt("drawMode",(int)m_drawMode);
}
//---------------------------------------------------------------------//
void Tower::doGather()
{
	m_canGather = false; 
	this->setDrawMode(TowerDrawMode::Normal);
}
