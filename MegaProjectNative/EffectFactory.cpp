#include "StdAfx.h"
#include "EffectFactory.h"

#include "MUEnums.h"
#include "Player.h"
#include "Actor.h"



using namespace Ogre;

template<> EffectFactory* Ogre::Singleton<EffectFactory>::msSingleton = 0;

EffectFactory::EffectFactory(void)
{
}

EffectFactory::~EffectFactory(void)
{
}

void EffectFactory::createInstance(Game::Player* _owner, SkillOpcode opcode, Game::Actor* _actor)
{

}
