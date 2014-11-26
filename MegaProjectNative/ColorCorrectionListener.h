#pragma once
#include "stdafx.h"

class ColorCorrectionListener : public Ogre::CompositorInstance::Listener
{
public:
	ColorCorrectionListener(void);
	~ColorCorrectionListener(void);

	//
	Ogre::Vector4 Multiplier;

	void notifyViewportSize(int width, int height);
	virtual void notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
	virtual void notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
};

