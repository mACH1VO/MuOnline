#include "StdAfx.h"
#include "AnimationBlender.h"
#include "MUEnums.h"
#include "Actor.h"

namespace Utilities
{
AnimationBlender::AnimationBlender( Entity *entity ) : mEntity(entity) 
{
	this->isInitialized = false;
}


void AnimationBlender::init(const String &animation, bool l, Game::Actor* _owner)
{
	this->Owner = _owner;
	if (!mEntity->hasSkeleton())
		return;
	AnimationStateSet *set = mEntity->getAllAnimationStates();
	AnimationStateIterator it = set->getAnimationStateIterator();
	while(it.hasMoreElements())
	{
		AnimationState *anim = it.getNext();
		anim->setEnabled(false);
		anim->setWeight(0);
		anim->setTimePosition(0);
		std::string name = anim->getAnimationName();
		if (_owner->entity->hasSkeleton())
		{
			Animation* an = _owner->entity->getSkeleton()->getAnimation(name);
			an->setRotationInterpolationMode(Ogre::Animation::RotationInterpolationMode::RIM_LINEAR);
			an->setInterpolationMode(Ogre::Animation::InterpolationMode::IM_LINEAR);
		}
		//GameFramework::getSingletonPtr()->sceneManager->getAnimation();
	}
	
	//Ogre::Animation::setDefaultInterpolationMode(InterpolationMode::
	//_owner->entity->getAnimationState("")->

	mSource = mEntity->getAnimationState( animation );
	mSource->setEnabled(true);

	//////CALLBACK/////
	this->Owner->onAnimationStarted(mSource->getAnimationName());

	mSource->setWeight(1);
	mTimeleft = 0;
	mDuration = 1;
	mTarget = 0;
	complete = false;
	loop = l;
	this->isInitialized = true;
	this->isBlending = false;
} 
void AnimationBlender::blend( const String &animation, BlendingTransition transition, Real duration, bool l )
{
	if (!this->isInitialized)
		return;

	if (this->isBlending)
		this->isBlending = true;

	loop = l;
	if( transition == BlendingTransition::BlendSwitch )
	{
		if( mSource != 0 )
		{
			mSource->setEnabled(false);

			//////CALLBACK/////
			//this->Owner->onAnimationEnded(mSource->getAnimationName());
		}
		mSource = mEntity->getAnimationState( animation );
		mSource->setEnabled(true);

		//////CALLBACK/////
		//this->Owner->onAnimationStarted(mSource->getAnimationName() /*+ "111"*/);

		mSource->setWeight(1);
		mSource->setTimePosition(0);
		mTimeleft = 0;
	} 
	else 
	{ 
		AnimationState *newTarget = mEntity->getAnimationState( animation );
		if( mTimeleft > 0 )
		{
			// oops, weren't finished yet
			if( newTarget == mTarget )
			{
				// nothing to do! (ignoring duration here)
			}
			else if( newTarget == mSource )
			{
				// going back to the source state, so let's switch
				mSource = mTarget;
				mTarget = newTarget;
				mTimeleft = mDuration - mTimeleft; // i'm ignoring the new duration here
			}
			else
			{
				// ok, newTarget is really new, so either we simply replace the target with this one, or
				// we make the target the new source
				if( mTimeleft < mDuration * 0.5 )
				{
					// simply replace the target with this one
					mTarget->setEnabled(false);
					mTarget->setTimePosition(0); ///MIO
					//////CALLBACK/////
					//this->Owner->onAnimationEnded(mTarget->getAnimationName());

					mTarget->setWeight(0);
				}
				else
				{
					// old target becomes new source
					mSource->setEnabled(false);
					mSource->setTimePosition(0); ///MIO
					//////CALLBACK/////
					//this->Owner->onAnimationEnded(mSource->getAnimationName());

					mSource->setWeight(0);
					mSource = mTarget;
				}

				mTarget = newTarget;
				mTarget->setEnabled(true);

				//////CALLBACK/////
				//this->Owner->onAnimationStarted(mTarget->getAnimationName() /*+ "222"*/);

				mTarget->setWeight( 1.0 - mTimeleft / mDuration );
				mTarget->setWeight( 1.0 - 0.5 ); ///MIO
				mTarget->setTimePosition(0);
			}
		}
		else
		{
			//assert( target == 0, "target should be 0 when not blending" );
			//mSource->setEnabled(true);
			//mSource->setWeight(1);
			mTransition = transition;
			mTimeleft = mDuration = duration;

			///MIOOO
			/*if (mTarget != 0)
			{
				mTarget->setWeight(0);
				mTarget->setTimePosition(0);
			}*/
			///

			mTarget = newTarget;
			mTarget->setEnabled(true);

			//////CALLBACK/////
			//this->Owner->onAnimationStarted(mTarget->getAnimationName()+ "333");

			mTarget->setWeight(0);
			mTarget->setTimePosition(0);
		}
	}
}
void AnimationBlender::addTime( Real time )
{
	if (!this->isInitialized)
		return;

	if( mSource != 0 )
	{
		if( mTimeleft > 0 )
		{
			mTimeleft -= time;
			if( mTimeleft <= 0 )
			{
				// finish blending
				mSource->setEnabled(false);

				//////CALLBACK/////
				this->Owner->onAnimationEnded(mSource->getAnimationName());
				mSource->setTimePosition(0); ///MIO
				mSource->setWeight(0);
				mSource = mTarget;

				mSource->setEnabled(true);

				//////CALLBACK/////
				this->Owner->onAnimationStarted(mSource->getAnimationName() /*+ "AAA"*/);

				mSource->setWeight(1);
				//mTarget = 0;

				this->isBlending = false;
			}
			else
			{
				// still blending, advance weights
				mSource->setWeight(mTimeleft / mDuration);
					
				mTarget->setWeight(1.0 - mTimeleft / mDuration);

				if(mTransition == BlendingTransition::BlendWhileAnimating)
				{
					/*if ((mTarget->getTimePosition() + time) > mTarget->getLength())
					{
						//this is a trick to fire end anim event for looped anim!
						this->Owner->onAnimationEnded(mTarget->getAnimationName());
					}*/
					mTarget->addTime(time);
				}

				this->isBlending = true;
			}
		}
		if (mSource->getTimePosition() >= mSource->getLength())
		{
			this->Owner->onAnimationEnded(mSource->getAnimationName());
			//LogManager::getSingleton().logMessage("Completed " + mSource->getAnimationName());
			complete = true;
		}
		else
		{
			complete = false;
		}


		/*if ((mSource->getTimePosition() + time) > mSource->getLength())
		{
			//this is a trick to fire end anim event for looped anim!
			this->Owner->onAnimationEnded(mSource->getAnimationName());
		}*/


		mSource->addTime(time);
		mSource->setLoop(loop);
	}
}

void AnimationBlender::forceFinishBlend()
{
	if( mSource != 0 )
	{
				// finish blending
				mSource->setEnabled(false);

				//////CALLBACK/////
				//this->Owner->onAnimationEnded(mSource->getAnimationName());

				mSource->setWeight(0);
				mSource = mTarget;

				mSource->setEnabled(true);

				//////CALLBACK/////
				//this->Owner->onAnimationStarted(mSource->getAnimationName() /*+ "AAA"*/);

				mSource->setWeight(1);
				mTarget = 0;

				this->isBlending = false;
	}
}
}