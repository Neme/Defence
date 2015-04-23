#include "TowerUtils.h"
#include "Packet.h"

//---------------------------------------------------------------------//
void TowerHealth::operator+=(Packet& packet)
{
	if (m_health < m_maxHealth)
		m_health += packet.getStrength();
}
//---------------------------------------------------------------------//
void TowerHealth::operator-=(Packet& packet)
{
	if (m_health > 0)
		m_health -= packet.getStrength();
}
//---------------------------------------------------------------------//
int TowerHealth::operator++()
{
	return (m_health > m_maxHealth) ? ++m_health : m_health;
}
//---------------------------------------------------------------------//
int TowerHealth::operator--()
{
	return (m_health > 0) ? --m_health : m_health;
}
//---------------------------------------------------------------------//
void TowerHealth::operator=(int health)
{
	m_health = health;
}
//---------------------------------------------------------------------//
bool TowerHealth::operator==(int health)
{
	return m_health == health;
}
