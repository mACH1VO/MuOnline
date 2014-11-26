#pragma  once
#include "StdAfx.h"
#include "Actor.h"
#include "GameBitBuffer.h"

class ItemData;

namespace Messages
{
	class GameMessage;
	class AttributesSetValuesMessage;
}

namespace Game
{
class Map;

class Item : public Actor
{
public:
	Item(int sno, int _dynamicId);
	~Item(void);

	Map* map;

	ItemData* itemData;
	ActorType getActorType();

	MyGUI::Button* _itemLabel ;
	void _itemLabelClicked(MyGUI::WidgetPtr _sender);

	virtual void update(float timeSinceLastFrame);

	virtual void enterMap(Vector3 position, Quaternion q, float scale);

	virtual void handleAttributeMessage(Messages::AttributesSetValuesMessage* message);

	int Level;
	int Defense;
	int DefenseRate;
	int Durability_Cur;
	int Durability_Max;
	int Strength_Requeriment;
	int Dexterity_Requeriment;
	int Vitality_Requeriment;
	int Intelligence_Requeriment;
	int Level_Requeriment;
	
};

class InventorySize
{
public:
	InventorySize(void)
	{
		this->Width = 0;
		this->Height = 0;
	}
	InventorySize(int w, int h)
	{
		this->Width = w;
		this->Height = h;
	}
	~InventorySize(void)
	{
	}
	int Width;
	int Height;
};

class InventorySlot
{
public:
	int R;
	int C;

	InventorySlot() { }
	InventorySlot(int r, int c)
	{
		R = r;
		C = c;
	}

	void Parse(Networking::GameBitBuffer* buffer)
	{
		R = buffer->ReadInt(32);
		C = buffer->ReadInt(32);
	}

	void Encode(Networking::GameBitBuffer* buffer)
	{
		buffer->WriteInt(32, R);
		buffer->WriteInt(32, C);
	}

	void AsText(std::string b, int pad)
	{
		b.append(' ', pad);
		b.append("InventorySlot:");
		b.append(' ', pad++);
		b.append("{");
		b.append(' ', pad);
		b.append("R: " + Ogre::StringConverter::toString(R));
		b.append(' ', pad);
		b.append("C: " + Ogre::StringConverter::toString(C));
		b.append(' ', --pad);
		b.append("}");
	}

	std::string toString()
	{
		std::string ret = StringConverter::toString(this->R) + "x" + StringConverter::toString(this->C);
		return ret;
	}
};
}