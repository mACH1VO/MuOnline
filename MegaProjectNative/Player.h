#pragma once
#include "stdafx.h"
#include "Actor.h"
#include "MUEnums.h"

#define PLAYER_BASE_ANIMATION_SPEED 0.4

enum ActorType;
enum ClassType;
enum PlayerState;
enum SkillOpcode;
enum SkillSlot;

class TickTimer;
class ISkill;

namespace Messages
{
	class GameMessage;
	class AttributesSetValuesMessage;
}

namespace Utilities
{
	class MuPath;
	class AnimationBlender;
	class AnimationBlender2;
}

namespace Game
{

class Map;
class Equipment;
class PlayerInventory;
class StashInventory;
class ShopInventory;
class WingComponent;

class Player : public Actor
{
public:
	Player(int sno_id, int _dynamicId, bool _isMainPlayer);
	~Player(void);

	MyGUI::Widget* ChatWidget;
	MyGUI::EditBox* ChatWidgetEditBox;
	Map* map;
	
	PlayerInventory* inventory;
	StashInventory* stashInventory;
	ShopInventory* shopInventory;

	ISkill* currentSkill;

	std::map<SkillSlot, SkillOpcode> *skillSlots;

	std::map<unsigned short, SkillOpcode> *availableSkillSlots;

	ClassType classType;
	PlayerState playerState;
	std::string name;
	
	
	float moveSpeed;
	float translateSpeed;
	std::string GeneralCurrentAnimationName;
	Utilities::AnimationBlender* animationBlender;
	TickTimer* ttText;

	WingComponent* wingComponent;

	//status
	bool isTranslating;
	bool isMoving;
	bool isMainPlayer;
	bool isCastingSkill;
	bool hasInventoryOpened;
	bool hasShopOpened;
	bool hasVaultOpened;
	bool canWalk;

	bool hasWings;
	bool hasHorse;

	void Player::Consume(Messages::GameMessage* message);

	void Player::say(std::string text, float msTimeOut);
	ActorType getActorType();

	virtual Vector3 getPosition();
	virtual void setPosition(Vector3 position);

	virtual Quaternion getOrientation();
	virtual void setOrientation(Quaternion quaternion);

	virtual void update(float timeSinceLastFrame);

	virtual void enterMap(Vector3 position, Quaternion q, float scale);

	void MoveTo(Vector3 dest);
	void PlayAnimation( std::string AnimName, bool loop, BlendingTransition _transition = BlendingTransition::BlendWhileAnimating);
	void PlaySkill( SkillSlot skillSlot, Actor* _clicked );
	void PlaySkill( SkillSlot skillSlot, Vector3 _position );
	void StopMoving();
	void StopTranslating();

	void TranslateTo(Vector3 dest, float translationSpeed);

	void Player::fillSkillSlots();
	void Player::fillAvailableSkillSlots();

	virtual void Player::onAnimationStarted(string name);
	virtual void Player::onAnimationEnded(string name);

	virtual void handleAttributeMessage(Messages::AttributesSetValuesMessage* message);

	Ogre::SimpleSpline* simpleSpline;

	void inline setBaseAnimationSpeed(float speed)
	{
		this->BaseAnimationSpeed = speed;
	}
	void inline restoreBaseAnimationSpeed()
	{
		this->BaseAnimationSpeed = PLAYER_BASE_ANIMATION_SPEED;
	}
	float BaseAnimationSpeed;

	int Level;
	float Strength;
	float Agility;
	float Stamina;
	float Energy;
	int AvailableStatsPoints;

	float Hitpoints_Cur;
	float Hitpoints_Max;

	float Mana_Cur;
	float Mana_Max;

private: 

	void updateMovement(float elapsed);
	void updateTranslation(float elapsed);
	void updateAnimation(float elapsed);
	std::string selectRightAnimation(std::string animation_name);
	Utilities::MuPath* _currentMovementPath;
	Utilities::MuPath* _currentTranslationPath;
	Vector3 _lastSendedPosition;
};

}
