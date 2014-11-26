#pragma once
#include "stdafx.h"

class TestCompositorListener;
class GrayScaleListener;

class GloomListener;
class VignettingListener;
class ColorCorrectionListener;
class GlowListener;
class PoissonBlurListener;

class GFXManager: public Ogre::Singleton<GFXManager>
{
public:
	GFXManager(void);
	~GFXManager(void);

	GloomListener* gloomListener;
	VignettingListener* vignettingListener;
	ColorCorrectionListener* colorCorrectionListener;
	GlowListener* glowListener;
	PoissonBlurListener* poissonBlurListener;
};

