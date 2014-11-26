#pragma once
#include "stdafx.h"
#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"


namespace Messages
{
	class GameMessage;
	class ACDEnterMapMessage;
}

namespace Utilities
{
	class MuPath;
	class DotSceneLoader;

}

namespace Forests
{
	class PagedGeometry;
	class GrassLoader;
	class GrassLayer;
}

using namespace Ogre;

class OgreRecast;
class OgreDetourTileCache;
class InputGeom;
class TickTimer;

enum QueryFlags;

namespace Game
{
class Actor;
class Player;
class Monster;
class Item;
class NPC;


//enum ActorType;

class Map: public Ogre::Singleton<Map>, public OIS::MouseListener
{
public:
	Map(void);
	~Map(void);

	///////////////////
	/** SCENE LOADER **/
	//////////////////
	Ogre::TerrainGroup* mTerrainGroup;
	Utilities::DotSceneLoader* mLoader;
	/*Forests::PagedGeometry* mPGHandle;                      
	Forests::GrassLoader* mGrassLoaderHandle;               
	Forests::GrassLayer* mPGLayers[4];*/
	float* mPGLayerData[4];
	Ogre::Image mPGDensityMap;
	Ogre::Rect mPGDirtyRect;
	////////////////

	/////////////////////////////////
	/** NAVIGATION MESH AND RAYCASTING **/
	////////////////////////////////
	

	//bool queryCursorPosition(Ogre::Vector3 &rayHitPoint, unsigned long queryflags, int x, int y, Ogre::MovableObject **raycastedObject);
	//bool __rayQueryPointInScene(Ogre::Ray ray, Ogre::Vector3 &result, Ogre::MovableObject **foundMovable);
	void calculateAndDrawPath(Ogre::Vector3 beginPos, Ogre::Vector3 endPos, int pathNb, int targetId);
	////////////////


	/////////////////////////////////
	/** TIMERS **/
	////////////////////////////////
	TickTimer* tt_pathfind_timer;
	TickTimer* tt_selectactor_timer;
	////////////////////////////////

	virtual bool mouseMoved(const OIS::MouseEvent &evt);
	virtual bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	////////////////

	void Consume(Messages::GameMessage* message);

	void update(float timeSinceLastFrame);
	bool isLoaded;

	std::map<int, Player*>* playersMap;
	std::map<int, Monster*>* monstersMap;
	std::map<int, Item*>* itemsMap;
	std::map<int, NPC*>* npcMap;
	std::map<int, Actor*>* actorMap;

	Game::Actor* CurrentHoveredActor;

	void EnterActor(Actor* _actor, Vector3 pos, Quaternion q, float scale);
	void LeaveActor(Actor* _actor);

	void processRaycastingActors();

	Utilities::MuPath* FindPath(Ogre::Vector3 origin, Ogre::Vector3 dest);
	void Map::DrawPath(Utilities::MuPath* _path);

	void Load(std::string sceneFile);
	void Destroy();

private: 

	Ogre::ManualObject* path_manual_object;
	Ogre::SceneNode* path_scene_node;

	OgreRecast* mRecast;
	OgreDetourTileCache* mDetourTileCache;
	InputGeom* inputGeom;

};
}
