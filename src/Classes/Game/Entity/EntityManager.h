#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "Entity.h"
#include <memory>
#include <map>
#include <string>
#include "Util/Util.h"
#include "Tower.h"
#include "Edge.h"

class EntityManager
{

public:

	EntityManager();

	template<typename T, typename... TArgs>
	T* addEntity(TArgs&&... mArgs){
		T* entity = util::create<T>(std::forward<TArgs>(mArgs)...);
		m_entites.push_back(entity);

		//add entity to group map
		m_entitesGrouped[typeid(T).hash_code()].push_back(entity);

		return entity;
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

	void clear() { m_entites.clear(); }

private:
	std::vector<EntityBase*> m_entites;
	std::map<size_t /*type_hash*/, std::vector<EntityBase*>> m_entitesGrouped;

};

#endif // __ENTITY_MANAGER_H__
