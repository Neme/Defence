#include "Level.h"
#include <memory>
#include "../GameManager.h"

//---------------------------------------------------------------------//
Level::Level()
{
	m_entityManager = GameManager::get<EntityManager>();
}
//---------------------------------------------------------------------//
Level::~Level()
{

}
//---------------------------------------------------------------------//
void Level::clear()
{
	m_entityManager->removeAllEntities();
	//...
}

//---------------------------------------------------------------------//
