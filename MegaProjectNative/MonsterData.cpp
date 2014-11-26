#include "StdAfx.h"
#include "MonsterData.h"
#include "Item.h"
#include "rapidxml.hpp"


MonsterData::MonsterData(void)
{
}


MonsterData::~MonsterData(void)
{
}

void MonsterData::Parse(std::string file_name)
{
	rapidxml::xml_document<> XMLDoc;    // character type defaults to char

	rapidxml::xml_node<>* XMLRoot;

	Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(file_name);
	char* scene = strdup(stream->getAsString().c_str());
	XMLDoc.parse<0>(scene);

	// Grab the scene node
	XMLRoot = XMLDoc.first_node("MonsterData");

	rapidxml::xml_node<>* pElement;

	pElement = XMLRoot->first_node("MeshFileName");
	if (pElement)
	{
		this->MeshFileName = pElement->value();
	}

	stream->close();
	
}
