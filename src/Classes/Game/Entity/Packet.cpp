#include "Packet.h"
#include "../Layer/GameLayer.h"

using namespace cocos2d;


//---------------------------------------------------------------------//
Packet::Packet(Tower& startTower, Tower& destTower) 
:Entity{}, m_startTower{ &startTower }, m_destTower{ &destTower }
{
	m_edge = startTower.getEdge(destTower);
}
//---------------------------------------------------------------------//
bool Packet::init()
{
	if (!CocosBase::init())
		return false;

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
	this->setGLProgramState(glProgramState);

	return true;
}
//---------------------------------------------------------------------//
void Packet::update(float delta)
{
	//passed time
	m_timeAlreadyMoved += delta;


	auto origin = m_startTower->getPosition();
	auto destination = m_destTower->getPosition();
	auto control = m_edge->getMovecControlPoint();
	auto t = m_timeAlreadyMoved;
	

	float x = powf(1 - t, 2) * origin.x + 2.0f * (1 - t) * t * control.x + t * t * destination.x;
	float y = powf(1 - t, 2) * origin.y + 2.0f * (1 - t) * t * control.y + t * t * destination.y;
	this->setPosition(x,y);

	//every second
	if (m_timeAlreadyMoved > 1.0f) {
		m_timeAlreadyMoved = 0;

		//Go to next node
		auto lastStartTower = m_startTower;
		m_startTower = m_destTower;
		m_destTower = m_startTower->getRandomNextTower(*lastStartTower);

		//Get edge
		m_edge = m_startTower->getEdge(*m_destTower);

		//Send packet receive to the tower
		if (m_startTower->receivePacket(*this)) {
			this->deleteEntity<Packet>();
			return;
		}
			
		if (!m_edge) {
			this->deleteEntity<Packet>();
			return;
		}
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
