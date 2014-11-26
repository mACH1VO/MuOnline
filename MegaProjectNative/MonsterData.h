#pragma once
#include "stdafx.h"

using namespace Ogre;
namespace Game
{
	class InventorySize;
}
class MonsterData
{
public:
	MonsterData(void);
	~MonsterData(void);

	void MonsterData::Parse(std::string file_name);

	String MeshFileName ;

};

