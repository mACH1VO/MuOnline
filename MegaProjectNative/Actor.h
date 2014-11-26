#pragma once
#include "stdafx.h"
#include "IAttributable.h"

using namespace Ogre;
enum ActorType;

namespace Messages
{
	class AttributesSetValuesMessage;
}

namespace Game
{
	
class Actor : public Ogre::Any, public IAttributable
{
public:
	Actor(void);
	virtual  ~Actor(void);
	
	int dynamicId;

	bool isMouseHover;

	std::map<int, Ogre::MaterialPtr> *hoverMaterials;
	std::map<int, string> *originalMaterials;
	virtual ActorType getActorType();

	virtual Vector3 getPosition();
	virtual void setPosition(Vector3 position);

	virtual Quaternion getOrientation();
	virtual void setOrientation(Quaternion quaternion);

	virtual void setLocalVectorDirector(Vector3 vect);

	void setDirection(Vector3 direction);
	void Actor::lookAt(Vector3 position);

	String meshFileName;

	virtual void onMouseHover();
	virtual void onMouseLeave();
	virtual void onMouseClick(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	virtual void Actor::onAnimationStarted(string name);
	virtual void Actor::onAnimationEnded(string name);

	virtual void update(float timeSinceLastFrame);
	virtual void enterMap(Vector3 position, Quaternion q, float scale);
	SceneNode* sceneNode ;
	Entity* entity ;

	Entity* actualOutlineGlowEntity;
	SceneNode* actualOutlineGlowNode;

	virtual void Actor::handleAttributeMessage(Messages::AttributesSetValuesMessage* message);

private:
	Vector3 _localVectorDirector;

};

}