#ifndef __PACKET_H__
#define __PACKET_H__

#include "cocos2d.h"
#include "Edge.h"
#include "Entity.h"

enum PacketType : int
{
	Neutral,
	Ally,
	Enemy,
};

class Packet : public Entity<>
{
public:

	Packet(Tower& startTower, Tower& destTower);
	bool init() override;
	void update(float delta) override;

	void setPacketType(PacketType type);
	PacketType getPacketType() const _noexcept { return m_packetType; }

	void setEdge(Edge& edge) { m_edge = &edge; }
	Edge* getEdge() { return m_edge; }

	int getStrength() const _noexcept{ return m_strength; }
	void setStrength(int strength) _noexcept{ m_strength = strength; }

private:
	Edge* m_edge{ nullptr };
	Tower* m_startTower;
	Tower* m_destTower;
	float m_timeAlreadyMoved{ 0 };

	PacketType m_packetType{ PacketType::Neutral };

	//Gameplay
	int m_strength{1};

};

#endif // __PACKET_H__
