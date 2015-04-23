#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <memory>
#include "Util/Util.h"
#include <tuple>
#include "Level/LevelManager.h"
#include "Entity/EntityManager.h"
#include "Layer/LayerManager.h"


class GameManager
{
public:
	GameManager() 
	{

	}

	//Usage: GameManage::get<LevelManager>()
	template<typename T>
	static T* get() {
		return m_instance.m_managers.get<T>();
	}


private:

	static GameManager m_instance;


	util::DependencyContainer
	<
		LevelManager,
		EntityManager,
		LayerManager
	> 
	m_managers 
	{
		{}, // LevelManager
		{},	// EntityManager
		{}  // LayerManager
	};


};

#endif // __GAME_MANAGER_H__
