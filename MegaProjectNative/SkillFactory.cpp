#include "StdAfx.h"
#include "SkillFactory.h"

#include "MUEnums.h"
#include "Player.h"
#include "Actor.h"

#include "ISkill.h"
#include "HandSkill.h"
#include "TwistingSkill.h"
#include "CycloneSkill.h"
#include "DeathStabSkill.h"
#include "LungeSkill.h"
#include "SlashSkill.h"
#include "FallingSlashSkill.h"
#include "RaidSkill.h"
#include "ImpaleSkill.h"
#include "ComboSkill.h"
#include "DefenseSkill.h"
#include "StrikeofDestructionSkill.h"
#include "UppercutSkill.h"
#include "InnerSkill.h"
#include "RagefulBlowSkill.h"



using namespace Ogre;

template<> SkillFactory* Ogre::Singleton<SkillFactory>::msSingleton = 0;

SkillFactory::SkillFactory(void)
{
}

SkillFactory::~SkillFactory(void)
{
}

ISkill* SkillFactory::createInstance(Game::Player* _owner, SkillOpcode opcode, Game::Actor* _actor)
{
	ISkill* ret = 0;
	switch(opcode)
	{
	case SkillOpcode::Hand:
		{
			ret = new HandSkill(_owner, _actor);
			break;
		}
	case SkillOpcode::Uppercut:
		{
			ret = new UppercutSkill(_owner);
			break;
		}
	case SkillOpcode::Cyclone:
		{
			ret = new CycloneSkill(_owner, _actor);
			break;
		}
	case SkillOpcode::Lunge:
		{
			ret = new LungeSkill(_owner);
			break;
		}
	case SkillOpcode::Slash:
		{
			ret = new SlashSkill(_owner);
			break;
		}
	case SkillOpcode::FallingSlash:
		{
			ret = new FallingSlashSkill(_owner);
			break;
		}
	case SkillOpcode::Raid:
		{
			ret = new RaidSkill(_owner);
			break;
		}
	case SkillOpcode::Impale:
		{
			ret = new ImpaleSkill(_owner);
			break;
		}
	case SkillOpcode::Twisting:
		{
			ret = new TwistingSkill(_owner);
			break;
		}
	/*case SkillOpcode::Inner:
		{
			ret = new InnerSkill(_owner);
			break;
		}*/
	/*case SkillOpcode::DeathStab:
		{
			ret = new DeathStabSkill(_owner, _actor);
			break;
		}*/
	case SkillOpcode::RagefulBlow:
		{
			ret = new RagefulBlowSkill(_owner);
			break;
		}
	case SkillOpcode::Strike_of_Destruction:
		{
			ret = new StrikeofDestructionSkill(_owner);
			break;
		}
	case SkillOpcode::Combo:
		{
			ret = new ComboSkill(_owner);
			break;
		}
	case SkillOpcode::Defense_:
		{
			ret = new DefenseSkill(_owner);
			break;
		}
	default:
		LogManager::getSingletonPtr()->logMessage("could not find skill with that opcode = " + StringConverter::toString((int)opcode));
	}

	return ret;
}
