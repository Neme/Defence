#ifndef __TOWER_H__
#define __TOWER_H__

#include "cocos2d.h"
#include "Const.h"
#include "Entity.h"
#include <vector>


enum class TowerType : int 
{
	TYPE_NEUTRAL,
	TYPE_ALLY,
	TYPE_ENEMY,
};

enum class TowerJob : int
{
	JOB_NORMAL,
	JOB_SPAWNER,
};

class Packet;
class Edge;

class Tower : public Entity<>
{
public:
	Tower();

	bool init() override;


	//------------//

	void setParentTower(Tower& tower) { m_parentTower = &tower; }
	void addChildTower(Tower& tower) { m_childrenTowers.push_back(&tower); }
	Tower* getParentTower() { return m_parentTower; }
	

	//------------//
	//Neighbor tower accessors

	std::vector<Tower*> getChildrenTowers() { return m_childrenTowers; }
	std::vector<Tower*> getNeightborTowers();
	Tower* getRandomChildTower();
	Tower* getRandomNeighborTower();
	Tower* getRandomNextTower(const Tower& lastTower);

	//------------//

	bool hasVulnerableNeighborTower(TowerType friendType, Tower& sender);
	int getChildrenTowerCount() const noexcept { return m_childrenTowers.size(); }
	int getNeightborTowerCount() const noexcept { return m_childrenTowers.size() + (m_parentTower ? 1 : 0); }


	Edge* getEdge(const Tower& neighbor);
	Edge* getRandomNextEdge(const Tower& lastTower);
	Edge* getRandomNeighborEdge();

	//------------//

	inline void setPulseTime(float time)  { m_pulseTime = time; }
	float getPulseTime() const { return m_pulseTime; }
	void pulse(float delta);

	//------------//
	//return value = weather packet should be deleted
	bool receivePacket(Packet& packet);

	//------------//
	//Game mechanics

	unsigned int getHealth() const noexcept { return m_health; }
	inline void setHealth(unsigned int health) noexcept { m_health = health; }

	void setTowerType(TowerType type);
	TowerType getTowerType() const noexcept { return m_towerType; }

	void setTowerJob(TowerJob job);
	TowerJob getTowerJob() const noexcept { return m_towerJob; }


protected:
	size_t m_towerUuid;

	void initEventListener();

	//Tree structure
	std::vector<Tower*> m_childrenTowers;
	Tower* m_parentTower{ nullptr };

	float m_pulseTime{ 1.0f };
	float m_pulseTimeDelta{ 0.0f };

	//Game mechanics
	unsigned int m_health{ 5 };
	TowerType m_towerType;
	TowerJob m_towerJob;

};

#endif // __TOWER_H__
