#pragma once
#include "stdafx.h"

using namespace Ogre;

namespace Utilities
{
class AnimationBlendData
{
public:

	Ogre::AnimationState* animationState;
	float fadeSpeed;
	bool exist;

	AnimationBlendData(void)
	{
		this->exist = false;
	}
	AnimationBlendData(AnimationState* state, float speed)
	{
		this->exist = true;
		this->animationState = state;
		this->fadeSpeed = speed;
	}
	AnimationBlendData(AnimationState* state)
	{
		this->exist = true;
		this->animationState = state;
		this->fadeSpeed = 1;
	}
	~AnimationBlendData(void){}

	inline AnimationBlendData& operator = ( const AnimationBlendData& operatorData )
	{
		this->animationState = operatorData.animationState;
		this->fadeSpeed = operatorData.fadeSpeed;
		this->exist = operatorData.exist;
		return *this;
	}
};
}

