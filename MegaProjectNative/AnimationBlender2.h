#pragma once
#include "stdafx.h"
#include "MUEnums.h"
#include "AnimationBlendData.h"

enum BlendingTransition;

using namespace Ogre;
namespace Game
{
	class Actor;
}
namespace Utilities
{
class AnimationBlendData;
class AnimationBlender2
{
public:

private:
	Entity *mEntity;

	AnimationBlendData animationFadingIn;
	AnimationBlendData currentAnimation;
	std::vector<AnimationBlendData>* animationsFadingOut;

	Game::Actor* Owner;
	BlendingTransition mTransition;

public: 

	bool isInitialized;

	bool inline isBlending()
	{
		return true;
	}

	void blend( const String &animation, BlendingTransition transition, Real duration, bool loop = true );
	void addTime( Real time);
	void fadeOut(AnimationBlendData animation, float time);
	float utilGetNewWeight(float currentTime, float speedFactor);
	AnimationBlender2( Entity * entity);
	~AnimationBlender2();
	void init( const String &animation, bool loop, Game::Actor* _owner );
};
}