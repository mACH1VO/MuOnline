#include "StdAfx.h"
#include "TestCompositorListener.h"


TestCompositorListener::TestCompositorListener(void)
{
	this->BlurAmount = 0.5;
	this->Center = Ogre::Vector2(0.5, 0.5);
}


TestCompositorListener::~TestCompositorListener(void)
{
}

void TestCompositorListener::notifyViewportSize(int width, int height)
{

}
//---------------------------------------------------------------------------
void TestCompositorListener::notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	mat->load();
	Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();

	//fparams->setNamedConstant("BlurAmount", this->BlurAmount);
	//fparams->setNamedConstant("Center", this->Center);
}
//---------------------------------------------------------------------------
void TestCompositorListener::notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{

}
