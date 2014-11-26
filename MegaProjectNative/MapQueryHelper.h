#pragma once
#include "stdafx.h"
#include "MUEnums.h"

using namespace Ogre;
namespace Game
{
	class Actor;
	class Player;
	class Monster;
	class Item;
	class NPC;
}
namespace Utilities
{
class MapQueryHelper: public Ogre::Singleton<MapQueryHelper>
{
public:
	MapQueryHelper(void);
	~MapQueryHelper(void);

	//Ogre::MovableObject* queryGeneralFirstMOAtCursorPosition(int x, int y, bool polygonLevel = false);

	std::vector<Game::Item*> queryItemsAtCursorPosition(int x, int y );
	std::vector<Game::NPC*> queryNPCsAtCursorPosition(int x, int y);
	std::vector<Game::Monster*> queryMonstersAtCursorPosition(int x, int y);
	std::vector<Game::Player*> queryPlayersAtCursorPosition(int x, int y);
	std::vector<Game::Actor*> queryActorsAtCursorPosition(int x, int y);

	Game::Item* queryFirstItemAtCursorPosition(int x, int y, bool polygonLevel = false);
	Game::NPC* queryFirstNPCAtCursorPosition(int x, int y, bool polygonLevel = false);
	Game::Monster* queryFirstMonsterAtCursorPosition(int x, int y, bool polygonLevel = false);
	Game::Player* queryFirstPlayerAtCursorPosition(int x, int y, bool polygonLevel = false);
	Game::Actor* queryFirstActorAtCursorPosition(int x, int y, bool polygonLevel = false);


	Ogre::Vector3 raycastNavigationMesh(int x, int y);
	//std::vector<Entity*> queryEntitiesAtCursorPosition(int x, int y, bool polygonLevel = false);

private:
	Ogre::RaySceneQueryResult _baseQueryAtCursorPosition(int x, int y, Ogre::uint32 flags );
	Ogre::MovableObject* _getFirstMORaycastedAtPolygonLevel(Ogre::RaySceneQueryResult query_result, Ogre::Ray mouseRay);
};
}
