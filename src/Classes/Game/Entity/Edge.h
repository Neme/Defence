#ifndef __EDGE_H__
#define __EDGE_H__

#include "cocos2d.h"
#include "Entity.h"
#include "Tower.h"
#include "Const.h"

class Edge : public Entity<cocos2d::DrawNode>
{
public:

	Edge(Tower& startTower, Tower& endTower);
	~Edge();

	//TEST REMOVE
	Edge(const Edge&) {
		int s = 0;
	}

	void update(float delta) override;

	cocos2d::Vec2 getControlPoint() const noexcept { return m_controlPoint; }
	void setControlPoint(const cocos2d::Vec2& point) noexcept{ m_controlPoint = point; }

	Tower& getStartTower() { return *m_startTower; }
	void setStartTower(Tower& tower) { m_startTower = &tower; }

	Tower& getDestTower() { return *m_destTower; }
	void setDestTower(Tower& tower) { m_destTower = &tower; }

	float getEndgeWidth() const noexcept { return m_edgeWidth; }
	void setEndgeWidth(float width) noexcept { m_edgeWidth = width; }

	cocos2d::Color4F getEndgeColor() const noexcept { return m_edgeColor; }
	void setEndgeColor(const cocos2d::Color4F& color) noexcept{ m_edgeColor = color; }

private:
	Tower* m_startTower{ nullptr };
	Tower* m_destTower{ nullptr };

	//Control points for bezier curve calculation
	cocos2d::Vec2 m_controlPoint;
	cocos2d::Vec2 m_controlPointVelo;

	float m_timeDelta{ 0 };
	float m_timeSeed{ 0 };

	float m_edgeWidth{ 10.0f };
	cocos2d::Color4F m_edgeColor{ 0.1f, 0.1f, 0.1f, 1.0f };
};

#endif // __EDGE_H__
