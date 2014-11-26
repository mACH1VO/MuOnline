#pragma once
#include "stdafx.h"
#include "GameFramework.h"

enum SkillOpcode;

class ISkill;

namespace Game
{
	class Player;
	class Actor;
}

class EffectFactory: public Ogre::Singleton<EffectFactory>
{
public:
	EffectFactory(void);
	~EffectFactory(void);

	void createInstance(Game::Player* _owner, SkillOpcode opcode, Game::Actor* _actor);

	void inline playRandomEffect(Ogre::SceneNode* sn)
	{
		/*std::vector<string> effectList;
		effectList.push_back("atomicity");
		effectList.push_back("example_012");
		effectList.push_back("flareShield");
		effectList.push_back("lineStreak");
		effectList.push_back("sparks");
		effectList.push_back("teleport");
		effectList.push_back("mp_torch");
		effectList.push_back("example_004");

		int minn = 0;
		int maxx = effectList.size();

		int index = (int)Ogre::Math::RangeRandom(minn, maxx);

		string name = effectList[index];

		ParticleUniverse::ParticleSystemManager* pManager =
			ParticleUniverse::ParticleSystemManager::getSingletonPtr();

		ParticleUniverse::ParticleSystem* pSys = pManager->createParticleSystem("playRandomEffect" + Ogre::StringConverter::toString(GameFramework::getSingletonPtr()->pTimer->getMicrosecondsCPU()),
			name, GameFramework::getSingletonPtr()->sceneManager);

		SceneNode* mNode = sn;
		mNode->attachObject(pSys);
		pSys->setScale(Vector3::UNIT_SCALE * 2);
			//mNode->setScale(10, 10, 10);

		if (name == "mp_torch")
			pSys->setScale(Vector3::UNIT_SCALE * 10);

		if (name == "teleport")
			pSys->setScale(Vector3::UNIT_SCALE * 0.5);

		pSys->prepare();
		pSys->start(10);*/
	}
};

