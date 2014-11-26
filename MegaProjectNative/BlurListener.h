#pragma once
#include "stdafx.h"

class BlurListener : public Ogre::CompositorInstance::Listener
{
public:
	BlurListener(void);
	~BlurListener(void);

	//
	Ogre::Real fuzziness;
	float GaussianDistribution( float x, float y, float rho );
	void notifyViewportSize(int width, int height);
	virtual void notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
	virtual void notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
};

