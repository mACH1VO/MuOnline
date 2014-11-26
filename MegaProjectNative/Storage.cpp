#include "StdAfx.h"
#include "Storage.h"
#include "rapidxml.hpp"
#include "ItemData.h"

template<> Storage* Ogre::Singleton<Storage>::msSingleton = 0;

Storage::Storage(void)
{
	this->snoMap = new std::map<int, std::string>();
}

Storage::~Storage(void)
{

}

void Storage::loadsnoMap()
{
	rapidxml::xml_document<> XMLDoc;    // character type defaults to char

	rapidxml::xml_node<>* XMLRoot;

	Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource("ActorSNOList.xml");
	char* actor_sno_list = strdup(stream->getAsString().c_str());
	XMLDoc.parse<0>(actor_sno_list);

	int jaja = 0;

	XMLRoot = XMLDoc.first_node("ActorData");

	rapidxml::xml_node<>* pActorSNOMapList;
	rapidxml::xml_node<>* pElement;
	// Process node (*)
	pActorSNOMapList = XMLRoot->first_node("ActorSNOMapList");
	pElement = pActorSNOMapList->first_node("ActorSNOMap");
	while(pElement)
	{
		processSNONAMEPair(pElement);
		pElement = pElement->next_sibling("ActorSNOMap");
	}
	stream->close();
	ItemData* id = new ItemData();
	id->Parse("CrossBow02.xml");

}
void Storage::processSNONAMEPair(rapidxml::xml_node<>* XMLNode)
{
	rapidxml::xml_node<>* pSNO = XMLNode->first_node("SNO");
	if (pSNO)
	{
		rapidxml::xml_node<>* pFileName = XMLNode->first_node("FileName");
		if (pFileName)
		{
			std::string sno_str = pSNO->value();
			std::string fileName = pFileName->value();
			int sno = Ogre::StringConverter::parseInt(sno_str);
			this->snoMap->insert(std::make_pair(sno, fileName));
			//jaja = 1;
		}
	}
}
