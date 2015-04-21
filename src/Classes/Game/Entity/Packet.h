#ifndef __PACKET_H__
#define __PACKET_H__

#include "cocos2d.h"
#include "Edge.h"
#include "Entity.h"

enum PacketType : int
{
	PACKET_NEUTRAL,
	PACKET_ALLY,
	PACKET_ENEMY,
};

class Packet : public Entity<>
{
public:

	Packet(Tower& startTower, Tower& destTower);
	bool init() override;
	void update(float delta) override;

	void setPacketType(PacketType type);
	PacketType getPacketType() const noexcept { return m_packetType; }

	void setEdge(Edge& edge) { m_edge = &edge; }
	Edge* getEdge() { return m_edge; }

private:
	Edge* m_edge{ nullptr };
	Tower* m_startTower;
	Tower* m_destTower;
	float m_timeAlreadyMoved{ 0 };

	PacketType m_packetType{ PacketType::PACKET_NEUTRAL };

};

#endif // __PACKET_H__
