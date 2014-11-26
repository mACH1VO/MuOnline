#include "StdAfx.h"

#include "Actor.h"
#include "MUEnums.h"
#include "Map.h"
#include "MaterialUtil.h"
#include "IAttributable.h"

#include "GameMessage.h"
#include "AttributesSetValuesMessage.h"


namespace Game
{
Actor::Actor(void)
	:Any(),
	IAttributable()
{
	this->sceneNode = 0;
	this->entity = 0;

	this->actualOutlineGlowEntity = 0;
	this->actualOutlineGlowNode = 0;

	this->_localVectorDirector = Vector3::UNIT_Z;
	this->isMouseHover = false;

	this->hoverMaterials = new std::map<int, Ogre::MaterialPtr>();
	this->originalMaterials = new std::map<int, string>();
}


Actor::~Actor(void)
{
	if (Map::getSingletonPtr()->CurrentHoveredActor != 0)
	{
		if (Map::getSingletonPtr()->CurrentHoveredActor->dynamicId == this->dynamicId)
			Map::getSingletonPtr()->CurrentHoveredActor = 0;
	}
}


ActorType Actor::getActorType()
{
	return ActorType::Invalid_Actor;
}


Vector3 Actor::getPosition()
{
	return this->sceneNode->getPosition();
}
void Actor::setPosition(Vector3 position)
{
	this->sceneNode->setPosition(position);
}

Quaternion Actor::getOrientation()
{
	return this->sceneNode->getOrientation();
}
void Actor::setOrientation(Quaternion quaternion)
{
	this->sceneNode->setOrientation(quaternion);
}

void Actor::setLocalVectorDirector(Vector3 vect)
{
	this->_localVectorDirector = vect;
}

void Actor::onMouseHover()
{
	/*if (this->hoverMaterials->size() == 0)
	{
		if (this->entity != 0)
		{
			for (int i = 0; i < this->entity->getNumSubEntities(); i++)
			{
				SubEntity* se = this->entity->getSubEntity(i);
				string original_material_name = se->getSubMesh()->getMaterialName();
				MaterialPtr original_material = MaterialManager::getSingletonPtr()->getByName(original_material_name);
				(*this->originalMaterials)[i] = original_material_name;

				//Ogre::Technique* best_technique = original_material->getBestTechnique();
				//MaterialUtil::setTechniqueOutlinePass(best_technique);
				Ogre::MaterialPtr clonedMaterial = original_material->clone(original_material->getName() + "_hovered_" + Ogre::StringConverter::toString(this->dynamicId));
				Ogre::Pass* outline_pass = clonedMaterial->getBestTechnique()->createPass();
				outline_pass->setName("outline_pass");
				outline_pass->setDepthWriteEnabled(false);
				outline_pass->setFragmentProgram("glow_ps_cg");
				outline_pass->setVertexProgram("glow_vs_cg");
				outline_pass->setSceneBlending( Ogre::SceneBlendFactor::SBF_SOURCE_ALPHA, Ogre::SceneBlendFactor::SBF_ONE_MINUS_SOURCE_ALPHA);
				bool ret = clonedMaterial->getBestTechnique()->movePass(1, 0);
				(*this->hoverMaterials)[i] = clonedMaterial;
			}
		}
	}

	for (int i = 0; i < this->entity->getNumSubEntities(); i++)
	{
		MaterialPtr hoverMaterial = (*this->hoverMaterials)[i];
		string hoverMaterialName = hoverMaterial->getName();
		this->entity->getSubEntity(i)->setMaterialName(hoverMaterialName);
		this->entity->setCastShadows(true);
	}*/

	this->isMouseHover = true;
}
void Actor::onMouseLeave()
{
	/*for (int i = 0; i < this->entity->getNumSubEntities(); i++)
	{
		string originalMaterialName = (*this->originalMaterials)[i];
		this->entity->getSubEntity(i)->setMaterialName(originalMaterialName);
	}*/
	this->isMouseHover = false;
}

void Actor::onMouseClick(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{

}
void Actor::update(float timeSinceLastFrame)
{

}
void Actor::enterMap(Vector3 position, Quaternion q, float scale)
{

}
void Actor::setDirection(Vector3 direction)
{
	//Direction = Direction - new Vector3(0, Direction.y, 0); //trick
	//Direction.Normalise();
	//this->sceneNode->lookAt(direction, Node::TransformSpace::TS_WORLD, this->_localVectorDirector);
	//this->sceneNode->setDirection(this->getPosition() + Vector3::UNIT_Y * 100, Node::TransformSpace::TS_WORLD, Vector3::UNIT_Y );
	this->sceneNode->setDirection(direction, Node::TransformSpace::TS_WORLD, this->_localVectorDirector );
	//Ogre::LogManager::getSingleton().logMessage(Ogre::StringConverter::toString(direction));

}

void Actor::lookAt(Vector3 position)
{
	position = Vector3(position.x, 0, position.z);
	position.y = this->getPosition().y;

	Vector3 direction = (position - this->getPosition()).normalisedCopy();
	this->setDirection(direction);
}

void Actor::onAnimationStarted(string name)
{
	//LogManager::getSingletonPtr()->logMessage("onAnimationStarted " + name);
}
void Actor::onAnimationEnded(string name)
{
	//LogManager::getSingletonPtr()->logMessage("onAnimationEnded " + name);
}

void Actor::handleAttributeMessage(Messages::AttributesSetValuesMessage* message)
{
	IAttributable::handleAttributeMessage(message);
}

}