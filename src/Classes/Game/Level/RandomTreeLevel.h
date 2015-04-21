#ifndef __RANDOM_TREE_LEVEL_H__
#define __RANDOM_TREE_LEVEL_H__

#include "Level.h"
#include "Const.h"

class RandomTreeLevel : public Level
{
public:
	RandomTreeLevel();
	RandomTreeLevel(unsigned int depth);

	~RandomTreeLevel();


	void spawn() override;

	inline void setTowerNodeDepth(unsigned int val) noexcept { m_towerNodeDepth = val; }
	unsigned int getTowerNodeDepth() const noexcept { return m_towerNodeDepth; }

	inline void setMinChildCount(unsigned int val) noexcept { m_minChildCount = val; }
	unsigned int getMinChildCount() const noexcept{ return m_minChildCount; }

	inline void setMaxChildCount(unsigned int val) noexcept { m_maxChildCount = val; }
	unsigned int getMaxChildCount() const noexcept{ return m_maxChildCount; }

	inline void setMinEdgeLength(unsigned int val) noexcept { m_minEdgeLength = val; }
	unsigned int getMinEdgeLength() const noexcept{ return m_minEdgeLength; }

	inline void setMaxEdgeLength(unsigned int val) noexcept { m_maxEdgeLength = val; }
	unsigned int getMaxEdgeLength() const noexcept{ return m_maxEdgeLength; }

private:
	unsigned int m_towerNodeDepth{ 10 };
	unsigned int m_minChildCount{ 2 };
	unsigned int m_maxChildCount{ 5 };
	unsigned int m_minEdgeLength{ 150 };
	unsigned int m_maxEdgeLength{ 200 };
};

#endif // __RANDOM_TREE_LEVEL_H__
