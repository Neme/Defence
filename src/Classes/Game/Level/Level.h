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

	virtual void spawn(){};
	virtual void clear();
	
protected:
	EntityManager* m_entityManager;


};

#endif // __LEVEL_H__
