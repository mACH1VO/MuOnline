#include "StdAfx.h"

#include "WingComponent.h"
#include "MUEnums.h"

#include "Player.h"
#include "PlayerInventory.h"
#include "BaseInventory.h"
#include "Equipment.h"

using namespace Ogre;

namespace Game
{

WingComponent::WingComponent(Player* _owner)
{
	this->Owner = _owner;
	this->animationState = 0;
	this->wingAnimationSpeed = 0.5;
}

WingComponent::~WingComponent(void)
{

}

void WingComponent::update(float timeSinceLastFrame)
{
	if (this->Owner->inventory->equipment->isSlotEmpty(EquipmentSlotId::Wing))
	{
		this->animationState = 0;
		return;
	}
	if (!this->Owner->hasWings)
	{
		this->animationState = 0;
		return;
	}

	if (this->Owner->inventory->equipment->VisualWings == 0)
	{
		this->animationState = 0;
		return;
	}

	Entity* ent = this->Owner->inventory->equipment->VisualWings;

	if ((this->animationState == 0) /*|| (this->animationState != ent->getAnimationState("Play"))*/)
	{
		this->animationState = ent->getAnimationState("Play");
		this->animationState->setLoop(true);
		this->animationState->setEnabled(true);

		if (this->Owner->isMoving)
			this->animationState->addTime(timeSinceLastFrame * wingAnimationSpeed * 3);
		else
			this->animationState->addTime(timeSinceLastFrame * wingAnimationSpeed);
	}
	else
	{
		if (this->Owner->isMoving)
			this->animationState->addTime(timeSinceLastFrame * wingAnimationSpeed * 3);
		else
			this->animationState->addTime(timeSinceLastFrame * wingAnimationSpeed);
	}
}
}
