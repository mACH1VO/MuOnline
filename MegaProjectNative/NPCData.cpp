#include "StdAfx.h"
#include "NPCData.h"
#include "Item.h"
#include "rapidxml.hpp"


NPCData::NPCData(void)
{
}


NPCData::~NPCData(void)
{
}

void NPCData::Parse(std::string file_name)
{
	rapidxml::xml_document<> XMLDoc;    // character type defaults to char

	rapidxml::xml_node<>* XMLRoot;

	Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(file_name);
	char* scene = strdup(stream->getAsString().c_str());
	XMLDoc.parse<0>(scene);

	// Grab the scene node
	XMLRoot = XMLDoc.first_node("NPCData");

	rapidxml::xml_node<>* pElement;

	pElement = XMLRoot->first_node("MeshFileName");
	if (pElement)
	{
		this->MeshFileName = pElement->value();
	}

	pElement = XMLRoot->first_node("NPCType");
	if (pElement)
	{
		this->NPCType = Ogre::StringConverter::parseInt(pElement->value());
	}
	stream->close();
}
