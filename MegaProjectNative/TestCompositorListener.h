#pragma once
#include "stdafx.h"

using namespace Ogre;

class TestCompositorListener : public Ogre::CompositorInstance::Listener
{
public:
	TestCompositorListener(void);
	~TestCompositorListener(void);

	Ogre::CompositorInstance* compositorInstance;

	//Params!
	float BlurAmount;
	Ogre::Vector2 Center;

	void notifyViewportSize(int width, int height);

	virtual void notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
	virtual void notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
};

