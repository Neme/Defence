#ifndef __TOWER_H__
#define __TOWER_H__

#include "cocos2d.h"
#include "Const.h"
#include "Entity.h"
#include "TowerUtils.h"
#include <vector>
#include <map>


class Packet;
class Edge;

//----------------------------------------------------------//

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
	int getChildrenTowerCount() const _noexcept { return m_childrenTowers.size(); }
	int getNeightborTowerCount() const _noexcept { return m_childrenTowers.size() + (m_parentTower ? 1 : 0); }


	Edge* getEdge(const Tower& neighbor);
	Edge* getRandomNextEdge(const Tower& lastTower);
	Edge* getRandomNeighborEdge();

	//------------//

	void setPulseTime(float time);
	float getPulseTime() const { return m_pulseTime; }
	void pulse(float delta);

	void setDrawMode(TowerDrawMode drawMode);
	TowerDrawMode getDrawMode() const _noexcept{ return m_drawMode; };

	//------------//
	void receivePacket(Packet& packet);

	//------------//
	//Game mechanics

	TowerHealth& getHealth() { return m_health; }
	inline void setHealth(int health) { m_health = health; }

	void setTowerType(TowerType type);
	TowerType getTowerType() const _noexcept { return m_towerType; }

	void setTowerJob(TowerJob job);
	TowerJob getTowerJob() const _noexcept { return m_towerJob; }

	void doGather();

protected:

	void initEventListener();

	//Tree structure
	std::vector<Tower*> m_childrenTowers;
	Tower* m_parentTower{ nullptr };

	float m_pulseTime{ 1.0f };
	float m_pulseTimeDelta{ 0.0f };

	TowerDrawMode m_drawMode{ TowerDrawMode::Normal };

	//Game mechanics
	TowerHealth m_health{ 15 };
	TowerType m_towerType{TowerType::Neutral};
	TowerJob m_towerJob{ TowerJob::Normal };

	//Gather
	bool m_canGather{ false };
	float m_gatherTimeDelta{ 0.0f };
	float m_gatherTime{ 10.0f };

};

#endif // __TOWER_H__
