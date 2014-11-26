#pragma once
#include "stdafx.h"

class GrayScaleListener : public Ogre::CompositorInstance::Listener
{
public:
	GrayScaleListener(void);
	~GrayScaleListener(void);

	//
	float Intensity;

	void notifyViewportSize(int width, int height);
	virtual void notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
	virtual void notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
};

