#include "Edge.h"
#include <algorithm>

using namespace cocos2d;

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
	m_controlPointVelo *= (rand_0_1() * 20.0f + 10.0f) * (rand_0_1() > 0.5f ? -1.0f : 1.0f);

	///Random time seed so the edges do not wave simultaneously
	m_timeSeed = rand_0_1() * 10.0f;


	this->updateCullingRect();
}
//---------------------------------------------------------------------//
void Edge::update(float delta)
{
	m_timeDelta += delta;
	m_controlPointMoved = m_controlPoint + m_controlPointVelo*(sin(m_timeDelta / 3 + m_timeSeed));

	//Draw bezier curve
	this->clear();
	this->drawQuadBezier(
		m_startTower->getPosition(),
		m_controlPointMoved,
		m_destTower->getPosition(),
		m_edgeSegments,
		m_edgeColor
	);

	
}
//---------------------------------------------------------------------//
void Edge::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	bool visible = true;


	//-----------//
	// Culling
	auto screenSize = Director::getInstance()->getWinSize();
	auto screenRect = Rect{ 0, 0, screenSize.width, screenSize.height };

	//Need to check two points of the rect
	//First point
	Vec4 world;
	Vec3 scale;
	auto local = Vec4{
		m_cullingRect.origin.x,
		m_cullingRect.origin.y,
		0, 1
	};
	transform.transformVector(local, &world);
	transform.getScale(&scale);



	//Create world rect
	auto worldRect = Rect{
		world.x,
		world.y,
		m_cullingRect.size.width * scale.x,
		m_cullingRect.size.height * scale.y,
	};

	//checks if one of the corners is on screen
	//basic origin and origin+size check

	visible = screenRect.containsPoint(worldRect.origin) || screenRect.containsPoint(worldRect.origin + worldRect.size);

	//if origin and origin+size are not on screen check the two other corners
	if (!visible) {
		visible = screenRect.containsPoint(worldRect.origin + Vec2{ 0, worldRect.size.height }) ||
			screenRect.containsPoint(worldRect.origin + Vec2{ worldRect.size.width, 0 });
	}


	//-----------//
	//Set less segments if the camera is far away by a modified sigmoid function
	m_edgeSegments = scale.x / (0.10f + std::fabs(scale.x*0.10f)) + 2.0f;



	//Actual draw
	if (visible) {
		CocosBase::draw(renderer, transform, flags);
	}
	
}
//---------------------------------------------------------------------//
void Edge::updateCullingRect()
{
	//Set visible rect for culling
	auto leftPoint = m_startTower->getPosition();
	auto rightPoint = m_destTower->getPosition();


	if (m_startTower->getPositionX() > m_destTower->getPositionX())
		std::swap(leftPoint, rightPoint);


	m_cullingRect = {
		leftPoint.x,
		leftPoint.y,
		rightPoint.x - leftPoint.x,
		rightPoint.y - leftPoint.y,
	};

}

//---------------------------------------------------------------------//

