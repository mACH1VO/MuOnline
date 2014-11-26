#pragma once
#include "stdafx.h"
#include "MUEnums.h"

enum BlendingTransition;

using namespace Ogre;
namespace Game
{
	class Actor;
}
namespace Utilities
{
class AnimationBlender
{
public:

private:
	Entity *mEntity;
	AnimationState *mSource;
	AnimationState *mTarget;

	Game::Actor* Owner;
	BlendingTransition mTransition;

	bool loop;

public: 
	Real mTimeleft, mDuration;

	bool complete;
	bool isInitialized;
	bool isBlending;

	void blend( const String &animation, BlendingTransition transition, Real duration, bool l=true );
	void addTime( Real );
	Real getProgress() { return mTimeleft/ mDuration; }
	void AnimationBlender::forceFinishBlend();
	AnimationState *getSource() { return mSource; }
	AnimationState *getTarget() { return mTarget; }
	AnimationBlender( Entity *);
	~AnimationBlender() {}
	void init( const String &animation, bool l, Game::Actor* _owner );
};
}