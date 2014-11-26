#include "StdAfx.h"
#include "AnimationBlender2.h"
#include "MUEnums.h"
#include "Actor.h"
#include "AnimationBlendData.h"

namespace Utilities
{
AnimationBlender2::AnimationBlender2( Entity *entity ) 
{
	this->isInitialized = false;
	this->mEntity = entity;
	this->animationsFadingOut = new std::vector<AnimationBlendData>();
}

AnimationBlender2::~AnimationBlender2() 
{
	delete this->animationsFadingOut;
}
void AnimationBlender2::init(const String &animation, bool loop, Game::Actor* _owner)
{
	this->Owner = _owner;

	if (!mEntity->hasSkeleton())
		return;

	AnimationStateSet *set = mEntity->getAllAnimationStates();
	AnimationStateIterator it = set->getAnimationStateIterator();
	while(it.hasMoreElements())
	{
		AnimationState *anim = it.getNext();
		std::string name = anim->getAnimationName();
		if (_owner->entity->hasSkeleton())
		{
			Animation* an = _owner->entity->getSkeleton()->getAnimation(name);

			if (an->getRotationInterpolationMode() != Animation::RotationInterpolationMode::RIM_LINEAR)
				an->setRotationInterpolationMode(Ogre::Animation::RotationInterpolationMode::RIM_LINEAR);

			if (an->getInterpolationMode() != Ogre::Animation::InterpolationMode::IM_LINEAR)
				an->setInterpolationMode(Ogre::Animation::InterpolationMode::IM_LINEAR);
		}
	}

	this->currentAnimation = AnimationBlendData(mEntity->getAnimationState( animation ));
	
	this->currentAnimation.animationState->setEnabled(true);
	this->currentAnimation.animationState->setWeight(1);
	this->currentAnimation.animationState->setTimePosition(0);
	this->currentAnimation.animationState->setLoop(loop);

	this->animationFadingIn.exist = false;
	this->animationsFadingOut->clear();

	this->isInitialized = true;
} 
void AnimationBlender2::blend( const String &animation, BlendingTransition transition, Ogre::Real duration, bool loop )
{
	if (!this->isInitialized)
		return;

	if (this->currentAnimation.exist)
		if (this->currentAnimation.animationState->getAnimationName() == animation)
			return;

	if (this->animationFadingIn.exist)
		if (this->animationFadingIn.animationState->getAnimationName() == animation)
			return;

	std::vector<AnimationBlendData>::iterator it;
	for (it = this->animationsFadingOut->begin(); it != this->animationsFadingOut->end(); ++it)
	{
		if (it->animationState->getAnimationName() == animation)
			return;
	}


	if (transition == BlendingTransition::BlendSwitch)
	{
		//delete the current one
		//we could send it to the fading out list right?
		if (this->currentAnimation.exist)
		{
			this->currentAnimation.animationState->setEnabled(false);
			this->currentAnimation.animationState->setTimePosition(0);
			this->currentAnimation.exist = false;;
		}

		//delete the fading in, because we dont want it to be current in the future
		//we could send it to the fading out list right?
		if (this->animationFadingIn.exist)
		{
			this->animationFadingIn.animationState->setEnabled(false);
			this->animationFadingIn.animationState->setTimePosition(0);
			this->animationFadingIn.exist = false;
		}

		this->currentAnimation = AnimationBlendData(mEntity->getAnimationState( animation ));
		this->currentAnimation.animationState->setEnabled(true);
		this->currentAnimation.animationState->setWeight(1);
		this->currentAnimation.animationState->setTimePosition(0);
		this->currentAnimation.animationState->setLoop(loop);
	}

	if (transition == BlendingTransition::BlendWhileAnimating)
	{
		if (this->currentAnimation.exist)
		{
			this->fadeOut(this->currentAnimation, duration);
			this->currentAnimation.exist = false;
		}

		if (this->animationFadingIn.exist)
		{
			//this->fadeOut(this->animationFadingIn, duration);
			this->animationFadingIn.animationState->setEnabled(false);
			this->animationFadingIn.animationState->setWeight(0);
			this->animationFadingIn.animationState->setTimePosition(0);
			this->animationFadingIn.exist = false;
		}
		else
		{
			this->animationFadingIn = AnimationBlendData(mEntity->getAnimationState( animation ), duration);
			this->animationFadingIn.animationState->setTimePosition(0);
			this->animationFadingIn.animationState->setWeight(0);
			this->animationFadingIn.animationState->setEnabled(true);
			this->animationFadingIn.animationState->setLoop(loop);
		}
	}
}
void AnimationBlender2::addTime( Real time )
{
	if (!this->isInitialized)
		return;

	//update the current one!
	if (this->currentAnimation.exist)
	{
		this->currentAnimation.animationState->addTime(time);
	}

	//update the fadingin one!
	if (this->animationFadingIn.exist)
	{
		//advance weight!
		this->animationFadingIn.animationState->addTime(time);
		float new_weight = this->utilGetNewWeight(this->animationFadingIn.animationState->getTimePosition(), this->animationFadingIn.fadeSpeed);
		this->animationFadingIn.animationState->setWeight(new_weight);

		//it reached the current!, switch!
		if (this->animationFadingIn.animationState->getWeight() == 1)
		{
			//switch fading in to current!
			this->currentAnimation.exist = false;;
			this->currentAnimation = this->animationFadingIn;
			this->animationFadingIn.exist = false;;
		}
	}

	std::vector<std::vector<AnimationBlendData>::iterator> toDelete;
	toDelete.clear();
	//update fading outs!
	int sizeDebug = this->animationsFadingOut->size();
	std::vector<AnimationBlendData>::iterator it;
	for (it = this->animationsFadingOut->begin(); it != this->animationsFadingOut->end(); ++it)
	{
		AnimationBlendData fadingOut = *it;

		fadingOut.animationState->addTime(time);
		float new_weight = 1.0 - this->utilGetNewWeight(fadingOut.animationState->getTimePosition(), fadingOut.fadeSpeed);
		fadingOut.animationState->setWeight(new_weight);

		if (new_weight <= 0) //
		{
			fadingOut.animationState->setEnabled(false);
			//fadingOut.animationState->setTimePosition(0);
			fadingOut.animationState->setWeight(0);

			//this->animationsFadingOut->erase(it);
			toDelete.push_back(it);
		}
	}

	for (int i = 0; i < toDelete.size(); i++)
	{
		std::vector<AnimationBlendData>::iterator it = toDelete[i];
		this->animationsFadingOut->erase(it);
	}

}

void AnimationBlender2::fadeOut(AnimationBlendData animationBlendData, float time)
{
	animationBlendData.animationState->setWeight(1);
	animationBlendData.fadeSpeed = time;
	this->animationsFadingOut->push_back(animationBlendData);
}

float AnimationBlender2::utilGetNewWeight(float currentTime, float speedFactor)
{
	float currentPercent = (currentTime / speedFactor);

	if (currentPercent >= 1)
		return 1;
	else 
		return currentPercent;
}
}