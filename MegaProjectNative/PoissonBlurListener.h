#pragma once
#include "stdafx.h"

class PoissonBlurListener : public Ogre::CompositorInstance::Listener
{
public:
	PoissonBlurListener(void);
	~PoissonBlurListener(void);

	//
	float DiskRadius;
	Ogre::Vector2 InputSize;

	void notifyViewportSize(int width, int height);
	virtual void notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
	virtual void notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
};

