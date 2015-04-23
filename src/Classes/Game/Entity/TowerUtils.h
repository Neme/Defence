#ifndef __TOWER_UTILS_H__
#define __TOWER_UTILS_H__


#include "Const.h"

class Packet;

//----------------------------------------------------------//

enum class TowerType : int
{
	Neutral,
	Ally,
	Enemy,
};

enum class TowerJob : int
{
	Normal,
	Spawner,
};

enum class TowerDrawMode : int
{
	Normal,
	Gather,
};


//----------------------------------------------------------//

struct TowerHealth {

public:
	TowerHealth(){};

	TowerHealth(int health)
		: m_health{ health }
	{};

	int operator++();
	int operator--();

	void operator+=(Packet& packet);
	void operator-=(Packet& packet);

	void operator=(int health);
	bool operator==(int health);

	int getHealth() const _noexcept{ return m_health; }
	int getMaxHealth() const _noexcept{ return m_maxHealth; }

	void setHealth(int health) _noexcept{ m_health = health; }
	void setMaxHealth(int maxHealth) _noexcept{ m_maxHealth = maxHealth; }

	float getHealthPercentage() const _noexcept{ return (float)m_health / (float)m_maxHealth * 100.0f; }

	void reset() { m_health = m_maxHealth; }
	bool isFull() { return m_health == m_maxHealth; }

private:
	int m_health{ 0 };
	int m_maxHealth{ 20 };
};


#endif // __TOWER_UTILS_H__
