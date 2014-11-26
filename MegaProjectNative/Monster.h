#pragma  once
#include "StdAfx.h"
#include "Actor.h"

using namespace Ogre;

class MonsterData;

namespace Messages
{
	class GameMessage;
	class AttributesSetValuesMessage;
}

namespace Utilities
{
	class AnimationBlender;
}

namespace Game
{
class Map;
class Monster : public Actor
{
public:
	Monster(int sno_id, int _dynamicId);
	~Monster(void);

	Map* map;
	std::string name;
	bool isMoving;
	bool isMainPlayer;
	float translateSpeed;
	std::string GeneralCurrentAnimationName;
	Utilities::AnimationBlender* animationBlender;

	MonsterData* monsterData;


	ActorType getActorType();

	virtual Vector3 getPosition();
	virtual void setPosition(Vector3 position);

	virtual Quaternion getOrientation();
	virtual void setOrientation(Quaternion quaternion);

	virtual void update(float timeSinceLastFrame);


	virtual void enterMap(Vector3 position, Quaternion q, float scale);

	void MoveTo(Vector3 dest);
	void PlayAnimation(std::string AnimName, bool loop );
	void StopMoving();

	virtual void Monster::onMouseClick(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	virtual void Monster::onMouseHover();
	virtual void Monster::onMouseLeave();

	virtual void handleAttributeMessage(Messages::AttributesSetValuesMessage* message);

private: 

	void updateMovement(float elapsed);
	void updateAnimation(float elapsed);
	//std::string selectRightAnimation(std::string animation_name);
	//Utilities::MuPath* _currentPath;

};

}