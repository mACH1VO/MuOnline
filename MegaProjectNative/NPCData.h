#pragma once
#include "stdafx.h"

using namespace Ogre;

class NPCData
{
public:
	NPCData(void);
	~NPCData(void);

	void NPCData::Parse(std::string file_name);

	String MeshFileName ;
	int NPCType;

};

