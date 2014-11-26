#include "StdAfx.h"
#include "PoissonBlurListener.h"


PoissonBlurListener::PoissonBlurListener(void)
{
	this->DiskRadius = 1.6;
	this->InputSize = Ogre::Vector2(1024, 1024);
}


PoissonBlurListener::~PoissonBlurListener(void)
{
}

void PoissonBlurListener::notifyViewportSize(int width, int height)
{

}
//---------------------------------------------------------------------------
void PoissonBlurListener::notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	mat->load();
	/*Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();
	fparams->setNamedConstant("radius", 10);
	fparams->setNamedConstant("intensity", 1);*/

}
//---------------------------------------------------------------------------
void PoissonBlurListener::notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();
	fparams->setNamedConstant("DiskRadius", this->DiskRadius);
	fparams->setNamedConstant("InputSize", this->InputSize);
}
