#ifndef __ENTITY_BASE_H__
#define __ENTITY_BASE_H__

#include "cocos2d.h"


class EntityBase {
public:
	virtual ~EntityBase(){};

	void removeEntityFromParent() {
		m_ptrToCocosNode->removeFromParent();
	}

	template<typename T = cocos2d::Node>
	T* getCocosBase() {
		static_assert(std::is_base_of<cocos2d::Node, T>::value, "Entity must inherit from a cocos::node");
		return dynamic_cast<T*>(m_ptrToCocosNode);
	}

protected:
	cocos2d::Node* m_ptrToCocosNode{ nullptr };
};



#endif // __ENTITY_BASE_H__
