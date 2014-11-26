#pragma  once
#include "StdAfx.h"
#include "Actor.h"

using namespace Ogre;

namespace Messages
{
	class GameMessage;
	class AttributesSetValuesMessage;
}
namespace Utilities
{
	class AnimationBlender;
}
class NPCData;
namespace Game
{
class Map;
class NPC : public Actor
{
public:
	NPC(int sno_id, int _dynamicId);
	~NPC(void);

	Map* map;

	std::string name;

	std::string GeneralCurrentAnimationName;
	Utilities::AnimationBlender* animationBlender;

	MyGUI::EditBox* nameEditBox;
	ActorType getActorType();

	NPCData* Data;

	virtual Vector3 getPosition();
	virtual void setPosition(Vector3 position);

	virtual Quaternion getOrientation();
	virtual void setOrientation(Quaternion quaternion);

	virtual void NPC::onMouseClick(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	virtual void NPC::onMouseHover();
	virtual void NPC::onMouseLeave();

	virtual void update(float timeSinceLastFrame);

	virtual void enterMap(Vector3 position, Quaternion q, float scale);

	virtual void handleAttributeMessage(Messages::AttributesSetValuesMessage* message);

	void PlayAnimation(std::string AnimName, bool loop );

private:
	void updateAnimation(float elapsed);
	//std::string selectRightAnimation(std::string animation_name);
	//Utilities::MuPath* _currentPath;
};
}