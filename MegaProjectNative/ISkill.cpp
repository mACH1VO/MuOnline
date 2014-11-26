#include "StdAfx.h"
#include "ISkill.h"
#include "MUEnums.h"
#include "TickTimer.h"

ISkill::ISkill(Game::Player* _owner, int _timeOut)
{
	this->owner = _owner;
	this->isFinished = false;
	this->tt_timeOut = new TickTimer(_timeOut);
	this->secondsElapsed = 0;
}

ISkill::~ISkill(void)
{
	//Ogre::LogManager::getSingletonPtr()->logMessage("ISkill Destructor Called");
	delete this->tt_timeOut;
}

SkillOpcode ISkill::getOpcode()
{
	return SkillOpcode::Invalid;
}

void ISkill::start()
{

}
void ISkill::update(float elapsed)
{
	if (this->tt_timeOut != 0)
	{
		if (this->tt_timeOut->TimedOut())
		{
			if (!this->isFinished)
			{
				this->finish();
			}
		}
	}
	this->secondsElapsed = this->secondsElapsed + elapsed;
}
void ISkill::finish()
{
	this->isFinished = true;
}

void ISkill::onAnimationStarted(string name)
{

}
void ISkill::onAnimationEnded(string name)
{

}