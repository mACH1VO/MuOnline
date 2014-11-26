#include "StdAfx.h"
#include "MapQueryHelper.h"
#include "GameFramework.h"
#include "MUEnums.h"
#include "RecastInputGeom.h"

template<> Utilities::MapQueryHelper* Ogre::Singleton<Utilities::MapQueryHelper>::msSingleton = 0;

namespace Utilities
{
MapQueryHelper::MapQueryHelper(void)
{
}


MapQueryHelper::~MapQueryHelper(void)
{
}

/*Ogre::Entity* MapQueryHelper::queryGeneralFirstEntityAtCursorPosition(int x, int y, bool polygonLevel = false)
{
	Ogre::RaySceneQueryResult queryResult = this->_baseQueryAtCursorPosition(x, y, QueryFlags::DEFAULT_MASK, polygonLevel);
}*/

std::vector<Game::Item*> MapQueryHelper::queryItemsAtCursorPosition( int x, int y )
{
	Ogre::RaySceneQueryResult queryResult = this->_baseQueryAtCursorPosition(x, y, QueryFlags::ITEM_MASK);
	std::vector<Game::Item*> ret;
	for (auto it = queryResult.begin(); it != queryResult.end(); ++it)
	{
		Game::Item* Item = any_cast<Game::Item*>(it->movable->getUserAny());
		ret.push_back(Item);
	}

	return ret;
}

std::vector<Game::NPC*> MapQueryHelper::queryNPCsAtCursorPosition( int x, int y )
{
	Ogre::RaySceneQueryResult queryResult = this->_baseQueryAtCursorPosition(x, y, QueryFlags::NPC_MASK);
	std::vector<Game::NPC*> ret;
	for (auto it = queryResult.begin(); it != queryResult.end(); ++it)
	{
		Game::NPC* NPC = any_cast<Game::NPC*>(it->movable->getUserAny());
		ret.push_back(NPC);
	}

	return ret;
}
std::vector<Game::Monster*> MapQueryHelper::queryMonstersAtCursorPosition( int x, int y )
{
	Ogre::RaySceneQueryResult queryResult = this->_baseQueryAtCursorPosition(x, y, QueryFlags::MONSTER_MASK);
	std::vector<Game::Monster*> ret;
	for (auto it = queryResult.begin(); it != queryResult.end(); ++it)
	{
		
		Game::Monster* Monster = any_cast<Game::Monster*>(it->movable->getUserAny());
		ret.push_back(Monster);
	}

	return ret;
}

std::vector<Game::Player*> MapQueryHelper::queryPlayersAtCursorPosition( int x, int y )
{
	Ogre::RaySceneQueryResult queryResult = this->_baseQueryAtCursorPosition(x, y, QueryFlags::PLAYER_MASK);
	std::vector<Game::Player*> ret;
	for (auto it = queryResult.begin(); it != queryResult.end(); ++it)
	{
		Game::Player* Player = any_cast<Game::Player*>(it->movable->getUserAny());
		ret.push_back(Player);
	}

	return ret;
}

std::vector<Game::Actor*> MapQueryHelper::queryActorsAtCursorPosition( int x, int y )
{
	Ogre::RaySceneQueryResult queryResult = this->_baseQueryAtCursorPosition(x, y, QueryFlags::ACTOR_MASK);
	std::vector<Game::Actor*> ret;
	for (auto it = queryResult.begin(); it != queryResult.end(); ++it)
	{
		Game::Actor* Actor = any_cast<Game::Actor*>(it->movable->getUserAny());
		ret.push_back(Actor);
	}

	return ret;
}

/*std::vector<Entity*> MapQueryHelper::queryEntitiesAtCursorPosition(int x, int y, bool polygonLevel )
{
	Ogre::RaySceneQueryResult queryResult = this->_baseQueryAtCursorPosition(x, y, 0xfffffffff , polygonLevel);
	std::vector<Entity*> ret;
	for (auto it = queryResult.begin(); it != queryResult.end(); ++it)
	{
		ret.push_back((Ogre::Entity*)(it->movable));
	}
	return ret;
}*/

Game::Item* MapQueryHelper::queryFirstItemAtCursorPosition(int x, int y, bool polygonLevel)
{
	if (polygonLevel)
	{
		Ogre::RaySceneQueryResult query_result = _baseQueryAtCursorPosition(x, y, QueryFlags::ITEM_MASK);
		Camera* cam = GameFramework::getSingletonPtr()->camera;
		float x_percent = ((float)x / cam->getViewport()->getActualWidth());
		float y_percent = ((float)y / cam->getViewport()->getActualHeight());

		Ogre::Ray mouseRay = cam->getCameraToViewportRay(x_percent, y_percent);
		Ogre::MovableObject* mo = this->_getFirstMORaycastedAtPolygonLevel(query_result, mouseRay);
		
		if (mo != nullptr)
			return any_cast<Game::Item*>(mo->getUserAny());
		return nullptr;
	}
	else
	{
		std::vector<Game::Item*> ret = this->queryItemsAtCursorPosition(x, y );
		if (ret.size() > 0)
			return ret[0];
		return nullptr;
	}
}

Game::NPC* MapQueryHelper::queryFirstNPCAtCursorPosition(int x, int y, bool polygonLevel)
{

	if (polygonLevel)
	{
		Ogre::RaySceneQueryResult query_result = _baseQueryAtCursorPosition(x, y, QueryFlags::NPC_MASK);
		Camera* cam = GameFramework::getSingletonPtr()->camera;
		float x_percent = ((float)x / cam->getViewport()->getActualWidth());
		float y_percent = ((float)y / cam->getViewport()->getActualHeight());

		Ogre::Ray mouseRay = cam->getCameraToViewportRay(x_percent, y_percent);
		Ogre::MovableObject* mo = this->_getFirstMORaycastedAtPolygonLevel(query_result, mouseRay);

		if (mo != nullptr)
			return any_cast<Game::NPC*>(mo->getUserAny());
		return nullptr;
	}
	else
	{
		std::vector<Game::NPC*> ret = this->queryNPCsAtCursorPosition(x, y );
		if (ret.size() > 0)
			return ret[0];
		return nullptr;
	}
}

Game::Monster* MapQueryHelper::queryFirstMonsterAtCursorPosition(int x, int y, bool polygonLevel)
{
	if (polygonLevel)
	{
		Ogre::RaySceneQueryResult query_result = _baseQueryAtCursorPosition(x, y, QueryFlags::MONSTER_MASK);
		Camera* cam = GameFramework::getSingletonPtr()->camera;
		float x_percent = ((float)x / cam->getViewport()->getActualWidth());
		float y_percent = ((float)y / cam->getViewport()->getActualHeight());

		Ogre::Ray mouseRay = cam->getCameraToViewportRay(x_percent, y_percent);
		Ogre::MovableObject* mo = this->_getFirstMORaycastedAtPolygonLevel(query_result, mouseRay);

		if (mo != nullptr)
			return any_cast<Game::Monster*>(mo->getUserAny());
		return nullptr;
	}
	else
	{
		std::vector<Game::Monster*> ret = this->queryMonstersAtCursorPosition(x, y );
		if (ret.size() > 0)
			return ret[0];
		return nullptr;
	}
}

Game::Player* MapQueryHelper::queryFirstPlayerAtCursorPosition(int x, int y, bool polygonLevel)
{
	if (polygonLevel)
	{
		Ogre::RaySceneQueryResult query_result = _baseQueryAtCursorPosition(x, y, QueryFlags::PLAYER_MASK);
		Camera* cam = GameFramework::getSingletonPtr()->camera;
		float x_percent = ((float)x / cam->getViewport()->getActualWidth());
		float y_percent = ((float)y / cam->getViewport()->getActualHeight());

		Ogre::Ray mouseRay = cam->getCameraToViewportRay(x_percent, y_percent);
		Ogre::MovableObject* mo = this->_getFirstMORaycastedAtPolygonLevel(query_result, mouseRay);

		if (mo != nullptr)
			return any_cast<Game::Player*>(mo->getUserAny());
		return nullptr;
	}
	else
	{
		std::vector<Game::Player*> ret = this->queryPlayersAtCursorPosition(x, y );
		if (ret.size() > 0)
			return ret[0];
		return nullptr;
	}
}

Game::Actor* MapQueryHelper::queryFirstActorAtCursorPosition(int x, int y, bool polygonLevel)
{
	if (polygonLevel)
	{
		Ogre::RaySceneQueryResult query_result = _baseQueryAtCursorPosition(x, y, QueryFlags::ACTOR_MASK);
		Camera* cam = GameFramework::getSingletonPtr()->camera;
		float x_percent = ((float)x / cam->getViewport()->getActualWidth());
		float y_percent = ((float)y / cam->getViewport()->getActualHeight());

		Ogre::Ray mouseRay = cam->getCameraToViewportRay(x_percent, y_percent);
		Ogre::MovableObject* mo = this->_getFirstMORaycastedAtPolygonLevel(query_result, mouseRay);

		if (mo != nullptr)
			return any_cast<Game::Actor*>(mo->getUserAny());
		return nullptr;
	}
	else
	{
		std::vector<Game::Actor*> ret = this->queryActorsAtCursorPosition(x, y );
		if (ret.size() > 0)
			return ret[0];
		return nullptr;
	}
}

Ogre::RaySceneQueryResult MapQueryHelper::_baseQueryAtCursorPosition(int x, int y, Ogre::uint32 flags )
{
	Camera* cam = GameFramework::getSingletonPtr()->camera;

	float x_percent = ((float)x / cam->getViewport()->getActualWidth());
	float y_percent = ((float)y / cam->getViewport()->getActualHeight());

	Ogre::Ray mouseRay = cam->getCameraToViewportRay(x_percent, y_percent);
	Ogre::RaySceneQuery* mRayScnQuery = GameFramework::getSingletonPtr()->sceneManager->createRayQuery(Ogre::Ray());

	mRayScnQuery->setRay(mouseRay);
	mRayScnQuery->setSortByDistance(true);
	mRayScnQuery->setQueryMask((Ogre::uint32)flags);
	mRayScnQuery->setQueryTypeMask(SceneManager::ENTITY_TYPE_MASK);
	Ogre::RaySceneQueryResult query = mRayScnQuery->execute();
	GameFramework::getSingletonPtr()->sceneManager->destroyQuery(mRayScnQuery);
	return query;
	//MovableObject* mo = this->_getFirstMORaycastedAtPolygonLevel(query_result, mouseRay);

}

Ogre::MovableObject* MapQueryHelper::_getFirstMORaycastedAtPolygonLevel(Ogre::RaySceneQueryResult query_result, Ogre::Ray mouseRay)
{
	Ogre::Ray ray = mouseRay;
	Ogre::Real closest_distance = -1.0f;
	Ogre::Vector3 closest_result;

	for (size_t qr_idx = 0; qr_idx < query_result.size(); qr_idx++)
	{
		// Debug:
		//Ogre::LogManager::getSingletonPtr()->logMessage(query_result[qr_idx].movable->getName());
		//Ogre::LogManager::getSingletonPtr()->logMessage(query_result[qr_idx].movable->getMovableType());
		// stop checking if we have found a raycast hit that is closer
		// than all remaining entities
		if ((closest_distance >= 0.0f) &&
			(closest_distance < query_result[qr_idx].distance))
		{
			break;
		}

		// only check this result if its a hit against an entity
		if ((query_result[qr_idx].movable != NULL) &&
			((query_result[qr_idx].movable->getMovableType().compare("Entity") == 0)
			||query_result[qr_idx].movable->getMovableType().compare("ManualObject") == 0))
		{
			// mesh data to retrieve
			size_t vertex_count;
			size_t index_count;
			Ogre::Vector3 *vertices;
			unsigned long *indices;

			// get the mesh information
			if(query_result[qr_idx].movable->getMovableType().compare("Entity") == 0) {
				// For entities
				// get the entity to check
				Ogre::Entity *pentity = static_cast<Ogre::Entity*>(query_result[qr_idx].movable);

				InputGeom::getMeshInformation(pentity->getMesh(), vertex_count, vertices, index_count, indices,
					pentity->getParentNode()->_getDerivedPosition(),
					pentity->getParentNode()->_getDerivedOrientation(),
					pentity->getParentNode()->_getDerivedScale());
			} else {
				// For manualObjects
				// get the entity to check
				Ogre::ManualObject *pmanual = static_cast<Ogre::ManualObject*>(query_result[qr_idx].movable);

				InputGeom::getManualMeshInformation(pmanual, vertex_count, vertices, index_count, indices,
					pmanual->getParentNode()->_getDerivedPosition(),
					pmanual->getParentNode()->_getDerivedOrientation(),
					pmanual->getParentNode()->_getDerivedScale());
			}

			// test for hitting individual triangles on the mesh
			bool new_closest_found = false;
			for (int i = 0; i < static_cast<int>(index_count); i += 3)
			{
				float factor = 1;
				// check for a hit against this triangle
				std::pair<bool, Ogre::Real> hit = Ogre::Math::intersects(ray, vertices[indices[i]] * factor,
					vertices[indices[i+1]] * factor, vertices[indices[i+2]] * factor, true, true);

				// if it was a hit check if its the closest
				if (hit.first)
				{
					if ((closest_distance < 0.0f) ||
						(hit.second < closest_distance))
					{
						// this is the closest so far, save it off
						closest_distance = hit.second;
						new_closest_found = true;
					}
				}
			}


			// free the verticies and indicies memory
			delete[] vertices;
			delete[] indices;

			// if we found a new closest raycast for this object, update the
			// closest_result before moving on to the next object.
			if (new_closest_found)
			{
				closest_result = ray.getPoint(closest_distance);
				if(query_result[qr_idx].movable != NULL)
				{
					MovableObject* ret = query_result[qr_idx].movable;
					return ret;
				}
				
			}
		}
	}

	return nullptr;
}

Ogre::Vector3 MapQueryHelper::raycastNavigationMesh(int x, int y)
{
	Ogre::RaySceneQueryResult queryResult = this->_baseQueryAtCursorPosition(x, y, QueryFlags::NAVMESH_MASK);
	if (queryResult.size() > 0)
	{
		float distance = queryResult[0].distance;
		Camera* cam = GameFramework::getSingletonPtr()->camera;
		float x_percent = ((float)x / cam->getViewport()->getActualWidth());
		float y_percent = ((float)y / cam->getViewport()->getActualHeight());
		Ogre::Ray mouseRay = cam->getCameraToViewportRay(x_percent, y_percent);

		Vector3 intersection = mouseRay.getOrigin() + mouseRay.getDirection().normalisedCopy() * distance;
		return intersection;
	}
	return Vector3::ZERO;

}
}


