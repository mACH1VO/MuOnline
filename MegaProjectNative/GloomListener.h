#pragma once
#include "stdafx.h"

class GloomListener : public Ogre::CompositorInstance::Listener
{
public:
	GloomListener(void);
	~GloomListener(void);

	float GloomIntensity;

	float BaseIntensity;

	float GloomSaturation;

	float BaseSaturation;

	void notifyViewportSize(int width, int height);
	virtual void notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
	virtual void notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
};

