#include "StdAfx.h"
#include "VignettingListener.h"


VignettingListener::VignettingListener(void)
{
	this->Intensity = 0.6;
	this->Radius = 5;
}


VignettingListener::~VignettingListener(void)
{
}

void VignettingListener::notifyViewportSize(int width, int height)
{

}
//---------------------------------------------------------------------------
void VignettingListener::notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	mat->load();
	/*Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();
	fparams->setNamedConstant("radius", 10);
	fparams->setNamedConstant("intensity", 1);*/

}
//---------------------------------------------------------------------------
void VignettingListener::notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();
	fparams->setNamedConstant("Radius", this->Radius);
	fparams->setNamedConstant("Intensity", this->Intensity);
}
