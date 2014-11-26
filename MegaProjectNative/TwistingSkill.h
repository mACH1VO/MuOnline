#pragma once
#include "stdafx.h"
#include "ISkill.h"

namespace Game
{
	class Player;
}
class TickTimer;

enum SkillOpcode;

class TwistingSkill : public ISkill
{
public:
	TwistingSkill(Game::Player* _owner);
	~TwistingSkill(void);

	Ogre::SceneNode* _PSsceneNode;
	//ParticleUniverse::ParticleSystem* _particleSystem;
	Ogre::SceneNode* _sceneNode;
	Ogre::Entity* _entity;

	static float frequency;
	static float Amplitude;
	static float phase;

	SkillOpcode TwistingSkill::getOpcode();
	virtual void start();
	virtual void update(float elapsed);
	virtual void finish();

	virtual void TwistingSkill::onAnimationStarted(string name);
	virtual void TwistingSkill::onAnimationEnded(string name);
};

