#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "../Entity/EntityManager.h"
#include <memory>
#include <type_traits>

class Level
{
public:
	Level();
	virtual ~Level();
	
	//TEST!! REMOVE
	Level(const Level&) {
		auto s = 0;
	}

	virtual void spawn(){};
	virtual void clear();
	
protected:
	EntityManager* m_entityManager;


};

#endif // __LEVEL_H__
