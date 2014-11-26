#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
	class Actor;
}
class TickTimer;

enum SkillOpcode;
/*
class DeathStabSkill : public ISkill
{
public:
	DeathStabSkill(Game::Player* _owner, Game::Actor* _target);
	~DeathStabSkill(void);

	Ogre::SceneNode* _PSsceneNode;
	ParticleUniverse::ParticleSystem* _particleSystem;

	Game::Actor* target;
	SkillOpcode DeathStabSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void DeathStabSkill::onAnimationStarted(string name);
	virtual void DeathStabSkill::onAnimationEnded(string name);
};

*/