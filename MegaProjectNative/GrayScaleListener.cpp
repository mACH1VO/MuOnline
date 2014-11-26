#include "StdAfx.h"
#include "GrayScaleListener.h"


GrayScaleListener::GrayScaleListener(void)
{
}


GrayScaleListener::~GrayScaleListener(void)
{
}

void GrayScaleListener::notifyViewportSize(int width, int height)
{

}
//---------------------------------------------------------------------------
void GrayScaleListener::notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	//mat->load();
	//Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();
	//fparams->setNamedConstant("sampleOffsets", this->Intensity);

}
//---------------------------------------------------------------------------
void GrayScaleListener::notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
}
