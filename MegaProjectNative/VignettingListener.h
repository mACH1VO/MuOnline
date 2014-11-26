#pragma once
#include "stdafx.h"

class VignettingListener : public Ogre::CompositorInstance::Listener
{
public:
	VignettingListener(void);
	~VignettingListener(void);

	//
	float Intensity;
	float Radius;

	void notifyViewportSize(int width, int height);
	virtual void notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
	virtual void notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
};

