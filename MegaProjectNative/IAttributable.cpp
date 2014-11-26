#include "StdAfx.h"
#include "IAttributable.h"
#include "GameAttributes.h"
#include "MUEnums.h"

#include "GameMessage.h"
#include "AttributesSetValuesMessage.h"
#include "NetAttributeKeyValue.h"

using namespace Game;

IAttributable::IAttributable(void)
{
	//this->Attributes = new GameAttributes(this);
	this->currentAttributes = new std::vector<AttributeOpcode>();
}


IAttributable::~IAttributable(void)
{
	//delete this->Attributes;
	//delete this->currentAttributes;
}

void IAttributable::handleAttributeMessage(Messages::AttributesSetValuesMessage* message)
{
	for (int i = 0; i < message->atKeyVals->size(); i++)
	{
		Messages::NetAttributeKeyValue* keyVal = message->atKeyVals->at(i);

		AttributeOpcode attributeOpcode = (AttributeOpcode)keyVal->Index;

		if(!(std::find(this->currentAttributes->begin(), this->currentAttributes->end(), attributeOpcode) != this->currentAttributes->end())) 
		{
			/* this->currentAttributes does not contain attributeOpcode */
			this->currentAttributes->push_back(attributeOpcode);
		} 
	}
}
