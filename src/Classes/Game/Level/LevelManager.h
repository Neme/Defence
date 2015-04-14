#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__

#include "Level.h"
#include <vector>
#include <memory>
#include <type_traits>

class LevelManager
{
public:
	template<typename T>
	T* getCurrentLevel(){ return dynamic_cast<T*>(m_currentLevel); }

	template<typename T, typename... TArgs>
	void spawnLevel(TArgs&&... mArgs){
		static_assert(std::is_base_of<Level, T>::value, "spawnLevel can only spawn levels");
		auto lvl = new T{ std::forward<TArgs>(mArgs)... };
		lvl->spawn();
		m_currentLevel = static_cast<Level*>(lvl);
		m_levels.push_back(std::make_unique<T>(lvl));
	}

private:

	std::vector<std::unique_ptr<Level>> m_levels;
	Level* m_currentLevel{ nullptr };

};

#endif // __LEVEL_MANAGER_H__
