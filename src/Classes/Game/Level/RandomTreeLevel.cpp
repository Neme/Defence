#include "RandomTreeLevel.h"
#include "../Entity/Tower.h"

using namespace cocos2d;

//---------------------------------------------------------------------//
RandomTreeLevel::RandomTreeLevel()
{

}
//---------------------------------------------------------------------//
RandomTreeLevel::~RandomTreeLevel()
{

}
//---------------------------------------------------------------------//
void RandomTreeLevel::spawn()
{
	//Clear
	this->clear();

	//--------------------------------//

	//Algorithm to create towers
	//Create nodes recursively
	std::function<void(Tower&, int)> createNodes = [this, &createNodes](Tower& parentNode, unsigned int depth){


		//Return if max node depth is reached
		if (depth >= m_towerNodeDepth)
			return;

		//Get node count
		int nodeCount = CCRANDOM_0_1()*(m_maxChildCount - m_minChildCount) + m_minChildCount;


		for (int i = 0; i < nodeCount; i++) {

			//-----------------------//
			//Generate position
			auto parentVec = Vec2{ 0, 1 };

			//If tower has no parent i.e if tower is a main tower
			//Spawn child towers in 360 degree around the main tower
			if (parentNode.getParentTower() != nullptr) {
				parentVec = parentNode.getPosition() - parentNode.getParentTower()->getPosition();
				parentVec.normalize();
				parentVec = parentVec.rotateByAngle({ 0, 0 }, -1 + (M_PI / nodeCount*i));

			}

			//Else spawn towers only in 90 degree
			else {
				parentVec = parentVec.rotateByAngle({ 0, 0 }, (M_PI * 2 / nodeCount)*i);
			}

			//Set vector length parentVec is normalized
			parentVec *= (CCRANDOM_0_1() * (m_maxEdgeLength - m_minEdgeLength) + m_minEdgeLength);

			//Get final position
			auto newPos = parentNode.getPosition() + parentVec;

			//-----------------------//

			//Check if edges intersect by checking if any tower is in
			//the radius(m_maxEdgeLength) of the tower
			//return if it's the case
			for (auto itr : m_entityManager->getEntitiesByGroup<Tower>()) {
				float distance = (newPos - itr->getPosition()).length();
				if (distance < m_maxEdgeLength / 2) {
					return;
				}
			}

			//-----------------------//

			//Create towers
			auto tower = m_entityManager->addEntity<Tower>();
			tower->setParentTower(parentNode);
			parentNode.addChildTower(*tower);
			tower->setPosition(newPos);

			//Push tower to m_towers
			

			//Call recursive lambda function
			createNodes(*tower, ++depth);

		}

	};

	//Create main tower
	auto mainTower = m_entityManager->addEntity<Tower>();
	mainTower->setTowerType(TowerType::TYPE_ALLY);
	mainTower->setTowerJob(TowerJob::JOB_SPAWNER);
	

	//Call recursive lambda function
	createNodes(*mainTower, 0);

	//--------------------------------//

	//Spawn enemy tower as far away as possible
	std::multimap<float, Tower*> lastTowerMap;

	for (auto tower : m_entityManager->getEntitiesByGroup<Tower>()) {
		auto d = (Vec2{ 0, 0 } -tower->getPosition()).length();
		lastTowerMap.insert(std::make_pair(d, tower));
	}

	unsigned int maxEnemy = 2;
	unsigned int enemyCount = 0;

	for (auto itr = lastTowerMap.rbegin(); itr != lastTowerMap.rend(); ++itr, ++enemyCount) {
		if (enemyCount < maxEnemy) {
			itr->second->setTowerType(TowerType::TYPE_ENEMY);
			itr->second->setTowerJob(TowerJob::JOB_SPAWNER);
		}
	}

}
