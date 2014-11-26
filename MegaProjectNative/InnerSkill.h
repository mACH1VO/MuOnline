#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;
/*
class InnerSkill : public ISkill
{
public:
	InnerSkill(Game::Player* _owner);
	~InnerSkill(void);

	Ogre::SceneNode* _PSsceneNode;
	ParticleUniverse::ParticleSystem* _particleSystem;

	SkillOpcode InnerSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void InnerSkill::onAnimationStarted(string name);
	virtual void InnerSkill::onAnimationEnded(string name);
};
*/
