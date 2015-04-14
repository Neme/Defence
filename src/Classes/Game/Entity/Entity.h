#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
#include "Const.h"

template<class T = cocos2d::Sprite>
class Entity : public T
{
	static_assert(std::is_base_of<cocos2d::Node, T>::value, "Entity must derive from cocos2d::node");

public:
	Entity() {
		if (!T::init())
			return;
		this->retain();
	}

	virtual ~Entity() {
		this->release();
	}

private:



};

#endif // __ENTITY_H__
