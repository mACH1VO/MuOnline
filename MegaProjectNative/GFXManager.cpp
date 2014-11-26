#include "StdAfx.h"
#include "GFXManager.h"
#include "GameFramework.h"

#include "TestCompositorListener.h"
#include "GrayScaleListener.h"
#include "VignettingListener.h"
#include "ColorCorrectionListener.h"
#include "GloomListener.h"
#include "GlowListener.h"
#include "PoissonBlurListener.h"

template<> GFXManager* Ogre::Singleton<GFXManager>::msSingleton = 0;

GFXManager::GFXManager(void)
{
	CompositorInstance* ci;
	ci = Ogre::CompositorManager::getSingleton().addCompositor(GameFramework::getSingletonPtr()->Viewport, "Test");
	TestCompositorListener* listener = new TestCompositorListener();
	ci->setEnabled(false);
	ci->addListener(listener);

	
	ci = Ogre::CompositorManager::getSingleton().addCompositor(GameFramework::getSingletonPtr()->Viewport, "Glow");
	this->glowListener = new GlowListener();
	ci->setEnabled(false);
	ci->addListener(this->glowListener);

	/*ci = Ogre::CompositorManager::getSingleton().addCompositor(GameFramework::getSingletonPtr()->Viewport, "Grayscale");
	GrayScaleListener* listener2 = new GrayScaleListener();
	ci->setEnabled(false);
	ci->addListener(listener2);*/

	ci = Ogre::CompositorManager::getSingleton().addCompositor(GameFramework::getSingletonPtr()->Viewport, "ColorCorrection");
	this->colorCorrectionListener = new ColorCorrectionListener();
	ci->setEnabled(false);
	ci->addListener(colorCorrectionListener);

	ci = Ogre::CompositorManager::getSingleton().addCompositor(GameFramework::getSingletonPtr()->Viewport, "Gloom");
	this->gloomListener = new GloomListener();
	ci->setEnabled(true);
	ci->addListener(this->gloomListener);

	ci = Ogre::CompositorManager::getSingleton().addCompositor(GameFramework::getSingletonPtr()->Viewport, "Vignetting");
	this->vignettingListener = new VignettingListener();
	ci->setEnabled(true);
	ci->addListener(this->vignettingListener);

	//TEXTURE SHADOW
	Ogre::TexturePtr texture = GameFramework::getSingleton().sceneManager->getShadowTexture(0);
	Ogre::Viewport* l_ShadowMapViewport = texture->getBuffer()->getRenderTarget()->getViewport(0);
	ci = Ogre::CompositorManager::getSingleton().addCompositor(l_ShadowMapViewport, "PoissonBlur");
	this->poissonBlurListener = new PoissonBlurListener();
	ci->setEnabled(true);
	ci->addListener(this->poissonBlurListener);

}


GFXManager::~GFXManager(void)
{
}
