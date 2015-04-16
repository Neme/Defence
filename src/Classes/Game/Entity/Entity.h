#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
#include "Const.h"

enum class EntityTag : int {
	Remove = -2,
	// -1 is used as default tag in cocos
	None = 0,
	Tower = 1,
};


class EntityBase {
public:
	virtual ~EntityBase(){};

};

template<typename T = cocos2d::Sprite>
class Entity : public EntityBase, public T
{
	static_assert(std::is_base_of<cocos2d::Node, T>::value, "Entity must inherit from a cocos::node");

public:
	using CocosBase = T;

	virtual ~Entity(){};
};


#endif // __ENTITY_H__
