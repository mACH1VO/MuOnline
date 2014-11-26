#pragma once
#include "stdafx.h"

class GlowListener : public Ogre::CompositorInstance::Listener
{
protected:
	Ogre::MaterialPtr mBlackMat;
public:
	GlowListener();
	~GlowListener();

	Ogre::Technique *handleSchemeNotFound(unsigned short, const Ogre::String& schemeName, Ogre::Material*mat, unsigned short, const Ogre::Renderable*)
	{
		if (schemeName == "glow")
		{
			//LogManager::getSingleton().logMessage(">> adding glow to material: "+mat->getName());
			return mBlackMat->getTechnique(0);
		}
		return NULL;
	}

	void notifyViewportSize(int width, int height);
	virtual void notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
	virtual void notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
};

