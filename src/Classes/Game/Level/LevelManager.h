#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__

#include "Level.h"
#include "Const.h"
#include <memory>
#include <functional>
#include <vector>
#include <type_traits>

class GameLayer;

class LevelManager
{
public:
	LevelManager();
	~LevelManager(){};

	LevelManager(const LevelManager& other){};
	LevelManager& operator=(const LevelManager& other){ return *this; };

	template<typename T>
	T* getCurrentLevel(){ return dynamic_cast<T*>(m_currentLevel); }

	template<typename T, typename... TArgs>
	T* spawnLevel(TArgs&&... mArgs){
		static_assert(std::is_base_of<Level, T>::value, "spawnLevel can only spawn levels");
		auto lvl = new T{ std::forward<TArgs>(mArgs)... };
		lvl->spawn();
		m_currentLevel = static_cast<Level*>(lvl);
		m_levels.emplace_back(lvl);

		if (m_gameLayer)
			m_gameLayer->setGameLevel(*m_currentLevel);

		return dynamic_cast<T*>(m_currentLevel);
	}

	void setGameLayer(GameLayer& gameLayer) noexcept{ m_gameLayer = &gameLayer; }

private:

	std::vector<std::unique_ptr<Level>> m_levels;
	Level* m_currentLevel{ nullptr };

	GameLayer* m_gameLayer{ nullptr };
};

#endif // __LEVEL_MANAGER_H__
