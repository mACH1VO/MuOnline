#include "StdAfx.h"
#include "PlayerData.h"
#include "Item.h"
#include "rapidxml.hpp"


PlayerData::PlayerData(void)
{
	this->inventorySize = new Game::InventorySize(10,10);
}


PlayerData::~PlayerData(void)
{
	delete this->inventorySize;
}

void PlayerData::Parse(std::string file_name)
{
	rapidxml::xml_document<> XMLDoc;    // character type defaults to char

	rapidxml::xml_node<>* XMLRoot;

	Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(file_name);
	char* scene = strdup(stream->getAsString().c_str());
	XMLDoc.parse<0>(scene);

	// Grab the scene node
	XMLRoot = XMLDoc.first_node("PlayerData");

	rapidxml::xml_node<>* pElement;

	pElement = XMLRoot->first_node("MeshFileName");
	if (pElement)
	{
		this->MeshFileName = pElement->value();
	}

	pElement = XMLRoot->first_node("ItemEquipedMeshFileNames");
	if (pElement)
	{
		rapidxml::xml_node<>* pElement_str = pElement->first_node("string");
		if (pElement_str)
			this->ItemEquipedMeshFileNames = pElement_str->value();
	}

	pElement = XMLRoot->first_node("IdleAnim");
	if (pElement)
	{
		this->IdleAnim = pElement->value();
	}

	pElement = XMLRoot->first_node("WalkAnim");
	if (pElement)
	{
		this->WalkAnim = pElement->value();
	}

	pElement = XMLRoot->first_node("AttackAnim");
	if (pElement)
	{
		this->AttackAnim = pElement->value();
	}

	pElement = XMLRoot->first_node("SkillAnim");
	if (pElement)
	{
		this->SkillAnim = pElement->value();
	}

	pElement = XMLRoot->first_node("AttackAnim");
	if (pElement)
	{
		this->AttackAnim = pElement->value();
	}

	pElement = XMLRoot->first_node("SkinName");
	if (pElement)
	{
		this->SkinName = pElement->value();
	}

	pElement = XMLRoot->first_node("Name");
	if (pElement)
	{
		this->Name = pElement->value();
	}

	pElement = XMLRoot->first_node("SNOActor");
	if (pElement)
	{
		this->SNOActor = Ogre::StringConverter::parseInt(pElement->value());
	}

	pElement = XMLRoot->first_node("ItemType");
	if (pElement)
	{
		this->ItemType = pElement->value();
	}

	pElement = XMLRoot->first_node("BaseGoldValue");
	if (pElement)
	{
		this->BaseGoldValue = Ogre::StringConverter::parseInt(pElement->value());
	}

	pElement = XMLRoot->first_node("RequiredLevel");
	if (pElement)
	{
		this->RequiredLevel = Ogre::StringConverter::parseInt(pElement->value());
	}

	pElement = XMLRoot->first_node("DurabilityMin");
	if (pElement)
	{
		this->DurabilityMin = Ogre::StringConverter::parseInt(pElement->value());
	}

	pElement = XMLRoot->first_node("DurabilityDelta");
	if (pElement)
	{
		this->DurabilityDelta = Ogre::StringConverter::parseInt(pElement->value());
	}

	pElement = XMLRoot->first_node("WeaponDamageMin");
	if (pElement)
	{
		this->WeaponDamageMin = Ogre::StringConverter::parseInt(pElement->value());
	}

	pElement = XMLRoot->first_node("WeaponDamageDelta");
	if (pElement)
	{
		this->WeaponDamageDelta = Ogre::StringConverter::parseInt(pElement->value());
	}

	pElement = XMLRoot->first_node("ArmorValue");
	if (pElement)
	{
		this->ArmorValue = Ogre::StringConverter::parseInt(pElement->value());
	}

	pElement = XMLRoot->first_node("AttacksPerSecond");
	if (pElement)
	{
		this->AttacksPerSecond = Ogre::StringConverter::parseInt(pElement->value());
	}

	pElement = XMLRoot->first_node("InventorySize");
	if (pElement)
	{
		rapidxml::xml_node<>* pElement_w = pElement->first_node("Width");
		if (pElement_w)
			this->inventorySize->Width = Ogre::StringConverter::parseInt(pElement_w->value());

		rapidxml::xml_node<>* pElement_h = pElement->first_node("Height");
		if (pElement_h)
			this->inventorySize->Height = Ogre::StringConverter::parseInt(pElement_h->value());
		//this->AttacksPerSecond = Ogre::StringConverter::parseInt(pElement->value());
	}

	stream->close();

	
}
