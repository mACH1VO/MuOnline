#pragma once
#include "stdafx.h"
#include "rapidxml.hpp"

class Storage : public Ogre::Singleton<Storage>
{
public:
	Storage(void);
	~Storage(void);

	std::map<int, std::string> *snoMap;

	void loadsnoMap();
	void Storage::processSNONAMEPair(rapidxml::xml_node<>* XMLNode);
};

