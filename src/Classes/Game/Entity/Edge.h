#ifndef __EDGE_H__
#define __EDGE_H__

#include "cocos2d.h"
#include "Entity.h"
#include "Tower.h"
#include "Const.h"

class Edge : public Entity<cocos2d::DrawNode>
{
public:

	Edge(){};
	Edge(Tower& startTower, Tower& endTower);


	void update(float delta) override;

	cocos2d::Vec2 getMovecControlPoint() const noexcept{ return m_controlPointMoved; }
	void setMovedControlPoint(const cocos2d::Vec2& point) noexcept{ m_controlPointMoved = point; }

	Tower* getStartTower() { return m_startTower; }
	void setStartTower(Tower& tower) { m_startTower = &tower; }

	Tower* getDestTower() { return m_destTower; }
	void setDestTower(Tower& tower) { m_destTower = &tower; }

	float getEndgeWidth() const noexcept { return m_edgeSegments; }
	void setEndgeWidth(float width) noexcept { m_edgeSegments = width; }

	cocos2d::Color4F getEndgeColor() const noexcept { return m_edgeColor; }
	void setEndgeColor(const cocos2d::Color4F& color) noexcept{ m_edgeColor = color; }

	void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;


private:
	Tower* m_startTower{ nullptr };
	Tower* m_destTower{ nullptr };

	//Control points for bezier curve calculation
	cocos2d::Vec2 m_controlPoint;
	cocos2d::Vec2 m_controlPointVelo;
	cocos2d::Vec2 m_controlPointMoved;

	float m_timeDelta{ 0 };
	float m_timeSeed{ 0 };

	int m_edgeSegments{ 10.0f };
	cocos2d::Color4F m_edgeColor{ 0.1f, 0.1f, 0.1f, 1.0f };

	//Culling
	cocos2d::Rect m_cullingRect{ 0, 0, 0, 0 };
	void updateCullingRect();

};

#endif // __EDGE_H__
