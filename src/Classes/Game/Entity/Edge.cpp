#include "Edge.h"

USING_NS_CC;

//---------------------------------------------------------------------//
Edge::Edge(Tower& startTower, Tower& endTower)
{
	if (!DrawNode::init())
		return;

	m_startTower = &startTower;
	m_destTower = &endTower;

	this->scheduleUpdate();

	//Set bezier control point right between the two towers
	m_controlPoint = m_startTower->getPosition().getMidpoint(m_destTower->getPosition());

	//Calculate a random velocity perpendicular to the towers
	m_controlPointVelo = (m_startTower->getPosition() - m_destTower->getPosition()).getPerp();
	m_controlPointVelo.normalize();
	m_controlPointVelo *= (CCRANDOM_0_1() * 20.0f + 10.0f) * (CCRANDOM_0_1() > 0.5f ? -1.0f : 1.0f);

	///Random time seed so the edges do not wave simultaneously
	m_timeSeed = CCRANDOM_0_1() * 10.0f;

}
//---------------------------------------------------------------------//
Edge::~Edge()
{

}
//---------------------------------------------------------------------//
void Edge::update(float delta)
{
	m_timeDelta += delta;
	auto newControlPoint = m_controlPoint + m_controlPointVelo*(sin(m_timeDelta / 3 + m_timeSeed));

	//Draw bezier curve
	this->clear();
	this->drawQuadBezier(
		m_startTower->getPosition(),
		newControlPoint,
		m_destTower->getPosition(),
		m_edgeWidth,
		m_edgeColor
	);

}
//---------------------------------------------------------------------//