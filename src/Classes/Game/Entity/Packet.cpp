#include "Packet.h"
#include "../Layer/GameLayer.h"

using namespace cocos2d;


//---------------------------------------------------------------------//
Packet::Packet(Edge& edge)
{

	/*m_edge = &m_towerContainer->getEdge(startTower, destTower);

	this->setTextureRect({ 0, 0, 25, 25 });
	this->scheduleUpdate();

	switch (m_startTower->getTowerType())
	{
	case TowerType::TYPE_ALLY:		this->setPacketType(PacketType::PACKET_ALLY); break;
	case TowerType::TYPE_ENEMY:		this->setPacketType(PacketType::PACKET_ENEMY); break;
	default:break;
	}

	//Init shader
	if (!ShaderCache::getInstance()->getGLProgram("shader_packet")) {
		auto shader = GLProgram::createWithFilenames("shader/packet.vert", "shader/packet.frag");
		shader->link();
		shader->updateUniforms();
		ShaderCache::getInstance()->addGLProgram(shader, "shader_packet");
	}

	auto shader = ShaderCache::getInstance()->getGLProgram("shader_packet");

	auto glProgramState = GLProgramState::create(shader);
	glProgramState->setUniformVec2("packetSize", this->getContentSize());

	this->setGLProgram(shader);
	this->setGLProgramState(glProgramState);*/
}
//---------------------------------------------------------------------//
void Packet::update(float delta)
{
	//passed time
	m_timeAlreadyMoved += delta;

	//safety reasons
	if (!m_edge) {
		this->setTag((int)EntityTag::Remove);
		return;
	}

	auto origin = m_edge->getStartTower().getPosition();
	auto destination = m_edge->getDestTower().getPosition();
	auto control = m_edge->getControlPoint();
	auto t = m_timeAlreadyMoved;
	

	float x = powf(1 - t, 2) * origin.x + 2.0f * (1 - t) * t * control.x + t * t * destination.x;
	float y = powf(1 - t, 2) * origin.y + 2.0f * (1 - t) * t * control.y + t * t * destination.y;
	this->setPosition(x,y);

	//every second
	if (m_timeAlreadyMoved > 1.0f) {
		m_timeAlreadyMoved = 0;

		//Go to next node
	/*	auto last_tower = m_startTower;
		m_startTower = m_destTower;
		m_destTower = m_startTower->getRandomNextTower(last_tower);
		m_edge = &m_towerContainer->getEdge(m_startTower, m_destTower);



		//Send packet receive to the tower
		if (m_startTower->receivePacket(this)) {
			this->setTag((int)NodeTags::TAG_REMOVE);
		}
			*/
	
	}

}
//---------------------------------------------------------------------//
void Packet::setPacketType(PacketType type)
{
	m_packetType = type;

	switch (type)
	{
	case PacketType::PACKET_ALLY:	this->setColor({ 86, 195, 83 }); break;
	case PacketType::PACKET_ENEMY:	this->setColor({ 195, 83, 139 }); break;
	default: break;
	}
}
