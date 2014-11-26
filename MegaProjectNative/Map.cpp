#include "StdAfx.h"
#include "Map.h"

/*#include "PagedGeometry.h"
#include "GrassLoader.h"
#include "BatchPage.h"
#include "ImpostorPage.h"
#include "TreeLoader3D.h"*/

#include "DotSceneLoader.h"
#include "GameFramework.h"
#include "GameGUI.h"
#include "MuPath.h"

#include "GameMessage.h"
#include "ACDEnterMapMessage.h"

#include "Factory.h"
#include "Actor.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "NPC.h"

#include "TickTimer.h"

#include "MapQueryHelper.h"

#include "OgreRecast.h"
#include "RecastInputGeom.h"
#include "OgreDetourTileCache.h"


using namespace Ogre;
using namespace Utilities;

template<> Game::Map* Ogre::Singleton<Game::Map>::msSingleton = 0;

namespace Game
{
Map::Map(void)
{
	this->mTerrainGroup = 0;

	this->playersMap = new std::map<int, Player*>();
	this->monstersMap = new std::map<int, Monster*>();
	this->itemsMap = new std::map<int, Item*>();
	this->npcMap = new std::map<int, NPC*>();
	this->actorMap = new std::map<int, Actor*>();

	this->mLoader = 0;
	this->isLoaded = false;

	this->path_manual_object = GameFramework::getSingletonPtr()->sceneManager->createManualObject("path_manual_object");
	this->path_scene_node = GameFramework::getSingletonPtr()->sceneManager->getRootSceneNode()->createChildSceneNode("path_scene_node");
	this->path_scene_node->attachObject(this->path_manual_object);

	this->tt_pathfind_timer = new TickTimer(30);
	this->tt_selectactor_timer = new TickTimer(10);

	this->CurrentHoveredActor = 0;
}

Map::~Map(void)
{
	delete this->playersMap;
}

void Map::EnterActor(Actor* _actor, Vector3 pos, Quaternion q, float scale)
{
	this->actorMap->insert(std::make_pair(_actor->dynamicId, _actor));
	switch(_actor->getActorType())
	{
	case ActorType::Player:
		{
			Player* p = (Player*)_actor;
			p->enterMap(pos,q,scale);
			this->playersMap->insert(std::make_pair(p->dynamicId, p));

			if (p->isMainPlayer)
				GameFramework::getSingletonPtr()->mainPlayer = p;

			break;
		}
	case ActorType::Monster:
		{
			Monster* m = (Monster*)_actor;
			m->enterMap(pos,q,scale);
			this->monstersMap->insert(std::make_pair(m->dynamicId, m));

			break;
		}

		case ActorType::Item:
		{
			Item* i = (Item*)_actor;
			i->enterMap(pos,q,scale);
			this->itemsMap->insert(std::make_pair(i->dynamicId, i));

			break;
		}
		case ActorType::NPC:
			{
				NPC* npc = (NPC*)_actor;
				npc->enterMap(pos,q,scale);
				this->npcMap->insert(std::make_pair(npc->dynamicId, npc));

				break;
			}
	default:
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("[Error] actor type missing, type = " + Ogre::StringConverter::toString(_actor->getActorType()));
		}
	}
}

void Map::LeaveActor(Actor* _actor)
{
	//Actor* actor = this->actorMap->at(actor->dynamicId);
	this->actorMap->erase(_actor->dynamicId);

	switch(_actor->getActorType())
	{

	case ActorType::Player:
		{
			this->playersMap->erase(_actor->dynamicId);
			break;
		}
	case ActorType::Monster:
		{
			this->monstersMap->erase(_actor->dynamicId);
			break;
		}

	case ActorType::Item:
		{
			this->itemsMap->erase(_actor->dynamicId);
			break;
		}
	case ActorType::NPC:
		{
			this->npcMap->erase(_actor->dynamicId);
			break;
		}
	default:
		{
			LogManager::getSingletonPtr()->logMessage("[Map] LeaveActor error, id not recognized");
			break;
		}
	}
}

void Map::Load(std::string sceneFile)
{
	this->mLoader = new Utilities::DotSceneLoader();
	this->mLoader->parseDotScene(sceneFile, "General", GameFramework::getSingletonPtr()->sceneManager);

	std::vector<Ogre::Entity*> mNavmeshEnts;
			/*Ogre::Entity* mapE = GameFramework::getSingletonPtr()->sceneManager->createEntity("Map", "dungeon.mesh");
			Ogre::SceneNode* mapNode = GameFramework::getSingletonPtr()->sceneManager->getRootSceneNode()->createChildSceneNode("MapNode");
			mapNode->scale(Vector3(2,2,2));
			mapNode->attachObject(mapE);
			mNavmeshEnts.push_back(mapE);*/

			mRecast = new OgreRecast(GameFramework::getSingletonPtr()->sceneManager); 
			mDetourTileCache = new OgreDetourTileCache(mRecast);

			if (this->mLoader != 0)
			{
				if (this->mLoader->entityList->size() > 0)
				{
					ConfigFile cf;
					std::vector<Ogre::Entity*> srcMeshes;// =  std::vector<Ogre::Entity*>(this->mLoader->entityList->begin(), this->mLoader->entityList->end());
					bool could_find_plane = false;
					for (int i = 0; i < this->mLoader->entityList->size(); i++	)
					{
						Ogre::Entity* ent = this->mLoader->entityList->at(i);
						if (ent->getName() == "Plane#0")
						{
							//ent->setMaterialName("MyMaterial");
							ent->setMaterialName("PlaneMaterial");
							ent->setCastShadows(false);
							//ent->setVisible(false);
							//ent->getParentSceneNode()->setPosition(Vector3(0,0,0));
							srcMeshes.clear();
							srcMeshes.push_back(ent);
							could_find_plane = true;
						}
					}

					if (could_find_plane)
					{
						inputGeom = new InputGeom(srcMeshes);
					}
					else
					{
						//srcMeshes =  std::vector<Ogre::Entity*>(this->mLoader->entityList->begin(), this->mLoader->entityList->end());
						if (this->mLoader->getTerrainGroup() != 0)
						{
							inputGeom = new InputGeom(this->mLoader->getTerrainGroup(), srcMeshes);
						}
						else
						{
							inputGeom = new InputGeom(srcMeshes);
						}
					}
					

					

					if(mDetourTileCache->TileCacheBuild(inputGeom)) 
					{
						mDetourTileCache->drawNavMesh();
					} 
					else 
					{
						Ogre::LogManager::getSingletonPtr()->logMessage("ERROR: could not generate useable navmesh from mesh using detourTileCache.");
						return;
					}
				}
			}

			Ogre::SceneNode* mNavMeshNode = (Ogre::SceneNode*)GameFramework::getSingletonPtr()->sceneManager->getRootSceneNode()->getChild("RecastSN");
			int ttt = mNavMeshNode->numAttachedObjects();
			//mNavMeshNode->setVisible(true);
			for (int i = 0; i < mNavMeshNode->numAttachedObjects(); i++) 
			{
				Ogre::MovableObject *obj = mNavMeshNode->getAttachedObject(i);
				obj->setVisible(false);
				obj->setQueryFlags(QueryFlags::NAVMESH_MASK);
			}

			

	this->isLoaded = true;
}

void Map::Destroy()
{
	this->playersMap->clear();
	delete this->mLoader;
	this->isLoaded = false;
}

void Map::update(float timeSinceLastFrame)
{
	if (this->mLoader != 0)
	{
		/*int sizee = mLoader->mPGHandles.size();
		for(unsigned int ij = 0;ij < mLoader->mPGHandles.size();ij++)
		{
			mLoader->mPGHandles[ij]->update();
		}*/
	}

	std::map<int, Actor*>::iterator actor_it;

	for (actor_it = this->actorMap->begin(); actor_it != this->actorMap->end(); ++actor_it)
	{
		actor_it->second->update(timeSinceLastFrame);
	}

	if (!GameFramework::getSingletonPtr()->getGameGUI()->isCursorOnGUI)
	{
		if (GameFramework::getSingletonPtr()->isMBLeftPressed)
		{
			if (this->tt_pathfind_timer->TimedOut() && ((this->CurrentHoveredActor == 0)))
			{
				/*Ogre::Vector3 rayHitPoint;
				Ogre::MovableObject *mo;
				if(queryCursorPosition(rayHitPoint, QueryFlags::NAVMESH_MASK, GameFramework::getSingletonPtr()->lastMouseX, GameFramework::getSingletonPtr()->lastMouseY, &mo)) 
				{
						if (GameFramework::getSingletonPtr()->mainPlayer != 0)
						{
							GameFramework::getSingletonPtr()->mainPlayer->MoveTo(rayHitPoint);
						}
				}
				else
				{
					LogManager::getSingletonPtr()->logMessage("[WARN] UPDATE but no navmesh mask taycasted!");
				}*/

				
				if (GameFramework::getSingletonPtr()->mainPlayer != 0)
				{
					Vector3 intersection = MapQueryHelper::getSingletonPtr()->raycastNavigationMesh(GameFramework::getSingletonPtr()->lastMouseX, GameFramework::getSingletonPtr()->lastMouseY);
					GameFramework::getSingletonPtr()->mainPlayer->MoveTo(intersection);
				}

				this->tt_pathfind_timer->Reset();
			}
		}
	}

	if (this->tt_selectactor_timer->TimedOut())
	{
		this->processRaycastingActors();
		this->tt_selectactor_timer->Reset();
	}


}

void Map::Consume(Messages::GameMessage* message)
{
	switch(message->opcode)
	{
	case Opcodes::ACDEnterMapMessage:
		{
			Messages::ACDEnterMapMessage* msg = (Messages::ACDEnterMapMessage*)message;
			std::map<int, Actor*>* pendMap = Game::Factory::getSingletonPtr()->pendingActorsMap;
			if ( pendMap->find( msg->ActorId ) != pendMap->end() )
			{
				Game::Actor* actor = pendMap->at(msg->ActorId);
				this->EnterActor(actor, msg->Position, msg->Orientation, msg->Scale);
				pendMap->erase(msg->ActorId);
			}
			else
			{
				LogManager::getSingletonPtr()->logMessage("trying to enter map actor that was never created!");
			}
			break;
		}
	default:
		{
			LogManager::getSingletonPtr()->logMessage("[Map] Consume error in Map, id not recognized");
			break;
		}
	}
}

void Map::DrawPath(Utilities::MuPath* _path)
{
	this->path_manual_object->clear();
	// Create new manualobject for the line

	this->path_manual_object->begin("recastdebug", Ogre::RenderOperation::OT_LINE_STRIP) ;

	std::vector<Ogre::Vector3>::iterator it;
	for (it = _path->points->begin(); it != _path->points->end(); ++it)
	{
		Ogre::Vector3 point = *it;
		this->path_manual_object->position(point.x, point.y + 0.5, point.z);
		this->path_manual_object->colour(Ogre::ColourValue::Red); 
	}

	this->path_manual_object->end();
}

Utilities::MuPath* Map::FindPath(Ogre::Vector3 origin, Ogre::Vector3 dest)
{
	int ret = mRecast->FindPath(origin, dest, 0, 0) ;
	if( ret >= 0 )
	{
		//this->path_manual_object->begin("recastdebug", Ogre::RenderOperation::OT_LINE_STRIP);
		std::vector<Ogre::Vector3> path = this->mRecast->getPath(0);

		Utilities::MuPath* ret = new Utilities::MuPath(path);

		return ret;
	}
	else
	{
		return 0;
	}
}

void Map::processRaycastingActors()
{
	if (GameFramework::getSingletonPtr()->getGameGUI()->isCursorOnGUI)
		return;

	int x = GameFramework::getSingletonPtr()->lastMouseX;
	int y = GameFramework::getSingletonPtr()->lastMouseY;

	Game::Actor* actor = MapQueryHelper::getSingletonPtr()->queryFirstActorAtCursorPosition(x, y, true);
	if (actor != nullptr)
	{
		if (this->CurrentHoveredActor != 0)
		{
			//if i touch one, and there is no hovered, do this.
			if (this->CurrentHoveredActor->dynamicId == actor->dynamicId)
			{
				//continious collision
			}
			else
			{
				this->CurrentHoveredActor->onMouseLeave();
				actor->onMouseHover();
				this->CurrentHoveredActor = actor;
			}
		}
		else
		{
			//if i touch one, and there is no currently hovered, do this.
			actor->onMouseHover();
			this->CurrentHoveredActor = actor;
		}
	}
	else
	{
		if (this->CurrentHoveredActor != 0)
		{
			//if i dont touch, and there is one currently hovered, do this!
			this->CurrentHoveredActor->onMouseLeave();
			this->CurrentHoveredActor = 0;
		}
		else
		{
			//if i dont touch, and there is no currently hovered, do this.
		    //nothing!
		}
	}
}

/*bool Map::queryCursorPosition(Ogre::Vector3 &rayHitPoint, unsigned long queryflags, int x, int y, Ogre::MovableObject **rayHitObject)
{
	// Do ray scene query
	//send a raycast straight out from the camera at the center position
	Camera* cam = GameFramework::getSingletonPtr()->camera;

	float x_percent = ((float)x / cam->getViewport()->getActualWidth());
	float y_percent = ((float)y / cam->getViewport()->getActualHeight());

	Ogre::Ray mouseRay = cam->getCameraToViewportRay(x_percent, y_percent);
	Ogre::MovableObject *hitObject;
	if (__rayQueryPointInScene(mouseRay, rayHitPoint, &hitObject)) 
	{
		//raycastedObject = LAST_SELECTED;
		if ( Ogre::StringUtil::startsWith(hitObject->getName(), "recastmowalk", true) ) 
		{
			// Compensate for the fact that the ray-queried navmesh is drawn a little above the ground
			rayHitPoint.y = rayHitPoint.y - mRecast->getNavmeshOffsetFromGround();
		} 
		if(false) 
		{
			// Queried point was not on navmesh, find nearest point on the navmesh (if not possible returns exact point)
			mRecast->findNearestPointOnNavmesh(rayHitPoint, rayHitPoint);
		}
		// Pass pointer to hit movable
		if (rayHitObject)
			*rayHitObject = hitObject;

		return true;
	}
	//raycastedObject = NULL;
	return false;
}*/
/*
bool Map::__rayQueryPointInScene(Ogre::Ray ray, Ogre::Vector3 &result, Ogre::MovableObject **foundMovable)
{
	// TODO: destroy queries using scenemgr::destroyRayQuery or reuse one query object by storing it in a member variable
	Ogre::RaySceneQuery* mRayScnQuery = GameFramework::getSingletonPtr()->sceneManager->createRayQuery(Ogre::Ray());

	mRayScnQuery->setRay(ray);
	mRayScnQuery->setSortByDistance(true);
	mRayScnQuery->setQueryMask(0xfffffff);
	Ogre::RaySceneQueryResult& query_result = mRayScnQuery->execute();
	// at this point we have raycast to a series of different objects bounding boxes.
	// we need to test these different objects to see which is the first polygon hit.
	// there are some minor optimizations (distance based) that mean we wont have to
	// check all of the objects most of the time, but the worst case scenario is that
	// we need to test every triangle of every object.
	Ogre::Real closest_distance = -1.0f;
	Ogre::Vector3 closest_result;
	//Ogre::MovableObject *closest_movable;
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
				// check for a hit against this triangle
				std::pair<bool, Ogre::Real> hit = Ogre::Math::intersects(ray, vertices[indices[i]],
					vertices[indices[i+1]], vertices[indices[i+2]], true, true);

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
					*foundMovable = query_result[qr_idx].movable;
					//LAST_SELECTED = query_result[qr_idx].movable;
				}
			}
		}
	}

	// return the result
	if (closest_distance >= 0.0f)
	{
		// raycast success
		result = closest_result;
		//*closest_movable = LAST_SELECTED;
		//*foundMovable = closest_movable;
		return (true);
	}
	else
	{
		// raycast failed
		return (false);
	}

}
*/
void Map::calculateAndDrawPath(Ogre::Vector3 beginPos, Ogre::Vector3 endPos, int pathNb, int targetId)
{
	// Note that this calculated path is not actually used except for debug drawing.
	// DetourCrowd will take care of calculating a separate path for each of its agents.
	int ret = mRecast->FindPath(beginPos, endPos, pathNb, targetId) ;
	if( ret >= 0 )
		mRecast->CreateRecastPathLine(pathNb) ; // Draw a line showing path at specified slot
	else
		Ogre::LogManager::getSingletonPtr()->logMessage("ERROR: could not find a (full) path ( "+mRecast->getPathFindErrorMsg(ret)+" ). It's possible there is a partial path.");
	// We dont bother with partial paths as this is only for debug drawing. DetourCrowd handles this for us anyway.
}


bool Map::mouseMoved(const OIS::MouseEvent &evt)
{
	if (!GameFramework::getSingletonPtr()->getGameGUI()->isCursorOnGUI)
	{
		if (GameFramework::getSingletonPtr()->isMBLeftPressed)
		{
			if (this->tt_pathfind_timer->TimedOut() && (this->CurrentHoveredActor == 0))
			{
				if (GameFramework::getSingletonPtr()->mainPlayer != 0)
				{
					Vector3 intersection = MapQueryHelper::getSingletonPtr()->raycastNavigationMesh(GameFramework::getSingletonPtr()->lastMouseX, GameFramework::getSingletonPtr()->lastMouseY);
					GameFramework::getSingletonPtr()->mainPlayer->MoveTo(intersection);
				}
	
				this->tt_pathfind_timer->Reset();
			}
		}
	}
	return true;
}

bool Map::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	//checks for player movement!
	if (!GameFramework::getSingletonPtr()->getGameGUI()->isCursorOnGUI)
	{
		if (GameFramework::getSingletonPtr()->isMBLeftPressed)
		{
			if (this->CurrentHoveredActor == 0)
			{
				if (this->tt_pathfind_timer->TimedOut())
				{
					if (GameFramework::getSingletonPtr()->mainPlayer != 0)
					{
						Vector3 intersection = MapQueryHelper::getSingletonPtr()->raycastNavigationMesh(GameFramework::getSingletonPtr()->lastMouseX, GameFramework::getSingletonPtr()->lastMouseY);
						GameFramework::getSingletonPtr()->mainPlayer->MoveTo(intersection);
					}

					this->tt_pathfind_timer->Reset();
				}
			}
		}
	}

	//checks for skills casting!
	if (!GameFramework::getSingletonPtr()->getGameGUI()->isCursorOnGUI)
	{
		if (this->CurrentHoveredActor != 0)
		{
			//cast targeted skill
			this->CurrentHoveredActor->onMouseClick(evt, id);
		}
	}

	return true;
}

bool Map::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}

}

