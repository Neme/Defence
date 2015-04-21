#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
#include "Const.h"
#include "EntityBase.h"
#include "../GameManager.h"


enum class EntityTag : int {
	None = 0,
	Tower = 1,
};



template<typename T = cocos2d::Sprite>
class Entity : public EntityBase, public T
{
	static_assert(std::is_base_of<cocos2d::Node, T>::value, "Entity must inherit from a cocos::node");

public:
	using CocosBase = T;

	Entity() {
		m_ptrToCocosNode = this;
	}

	virtual ~Entity(){}

	template<typename U>
	void deleteEntity() {
		GameManager::get<EntityManager>()->removeEntity<U>(*this);
	}
};


#endif // __ENTITY_H__
