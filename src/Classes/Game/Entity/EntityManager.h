#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <memory>
#include <map>
#include <string>
#include "Util/Util.h"
#include "EntityBase.h"
#include "../Layer/GameLayer.h"

class EntityManager
{

public:

	EntityManager();


	template<typename T1, typename T2 = GameLayer, typename... TArgs>
	T1* addEntity(TArgs&&... mArgs) {
		auto entity = util::create<T1>(std::forward<TArgs>(mArgs)...);

		if (!entity)
			return nullptr;

		m_entites.push_back(entity);

		//add entity to group map
		m_entitesGrouped[typeid(T1).hash_code()].push_back(entity);

		//get Layer
		auto layer = GameManager::get<LayerManager>()->getLayer<T2>();
		layer->addChild(entity);

		return entity;
	}

	template<typename T>
	void removeEntity(EntityBase& entity) {
		auto typeHash = typeid(T).hash_code();
		if (m_entitesGrouped.count(typeHash)) {
			auto& vec = m_entitesGrouped[typeHash];
			vec.erase(std::remove(vec.begin(), vec.end(), &entity), vec.end());
			m_entites.erase(std::remove(m_entites.begin(), m_entites.end(), &entity), m_entites.end());
		}

		entity.getCocosBase()->removeFromParent();
	}

	//Usage: getEntitiesByGroup<Tower>()
	template<typename T>
	std::vector<T*> getEntitiesByGroup() {
		auto typeHash = typeid(T).hash_code();

		//Checks if typeHash is in m_entitesGrouped
		if (m_entitesGrouped.count(typeHash)) {
			std::vector<T*> tmp;
			for (auto itr : m_entitesGrouped[typeHash]) {
				tmp.push_back(dynamic_cast<T*>(itr));
			}
			return std::move(tmp);
		}
		
		//Returns empty vector if no entity was found
		return std::vector<T*>{};
	}

	void removeAllEntities() { 	
		for (auto entity : m_entites) {
			entity->removeEntityFromParent();
		}
		m_entites.clear();

		for (auto& itr : m_entitesGrouped) {
			itr.second.clear();
		}


	}

private:
	std::vector<EntityBase*> m_entites;
	std::map<size_t /*type_hash*/, std::vector<EntityBase*>> m_entitesGrouped;

};

#endif // __ENTITY_MANAGER_H__
