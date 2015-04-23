#ifndef __LAYER_MANAGER_H__
#define __LAYER_MANAGER_H__

#include "Const.h"
#include "cocos2d.h"
#include <map>
#include <memory>
#include <functional>
#include <vector>
#include <type_traits>

class LayerManager
{
public:
	LayerManager();


	template<typename T>
	T* getLayer() {
		if (m_layer.count(typeid(T).hash_code()) < 1)
			return nullptr;

		return dynamic_cast<T*>(m_layer[typeid(T).hash_code()]);
	}

	template<typename T>
	void setLayer(T* layer) {
		m_layer[typeid(T).hash_code()] = layer;
	}

	template<typename T>
	void setLayer(T& layer) {
		m_layer[typeid(T).hash_code()] = &layer;
	}




private:

	std::map<size_t /*hash*/, cocos2d::Layer* > m_layer;

};

#endif // __LAYER_MANAGER_H__
