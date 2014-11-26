#include "StdAfx.h"
#include "ColorCorrectionListener.h"


ColorCorrectionListener::ColorCorrectionListener(void)
{
}


ColorCorrectionListener::~ColorCorrectionListener(void)
{
}

void ColorCorrectionListener::notifyViewportSize(int width, int height)
{

}
//---------------------------------------------------------------------------
void ColorCorrectionListener::notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	mat->load();
	/*Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();
	fparams->setNamedConstant("radius", 10);
	fparams->setNamedConstant("intensity", 1);*/

}
//---------------------------------------------------------------------------
void ColorCorrectionListener::notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();
	/*fparams->setNamedConstant("radius", 10);
	fparams->setNamedConstant("intensity", 1);*/
}
