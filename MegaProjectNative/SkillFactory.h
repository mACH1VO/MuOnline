#pragma once
#include "stdafx.h"

enum SkillOpcode;

class ISkill;

namespace Game
{
	class Player;
	class Actor;
}

class SkillFactory: public Ogre::Singleton<SkillFactory>
{
public:
	SkillFactory(void);
	~SkillFactory(void);

	ISkill* createInstance(Game::Player* _owner, SkillOpcode opcode, Game::Actor* _actor);
};

