#pragma once
#include "stdafx.h"

namespace Game
{
class Player;
class WingComponent
{
public:
	WingComponent(Player* _owner);
	~WingComponent(void);

	float wingAnimationSpeed;
	Player* Owner;
	Ogre::AnimationState* animationState;
	void update(float timeSinceLastFrame);
};
}

