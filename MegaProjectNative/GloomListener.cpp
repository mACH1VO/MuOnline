#include "StdAfx.h"
#include "GloomListener.h"


GloomListener::GloomListener(void)
{
	this->GloomIntensity = 0.24;
	this->GloomSaturation = 1.34;
	this->BaseIntensity = 0.98;
	this->BaseSaturation = 1.36;
}


GloomListener::~GloomListener(void)
{
}

void GloomListener::notifyViewportSize(int width, int height)
{

}
//---------------------------------------------------------------------------
void GloomListener::notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	mat->load();
	/*Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();
	fparams->setNamedConstant("radius", 10);
	fparams->setNamedConstant("intensity", 1);*/

}
//---------------------------------------------------------------------------
void GloomListener::notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();
	fparams->setNamedConstant("GloomIntensity", this->GloomIntensity);
	fparams->setNamedConstant("GloomSaturation", this->GloomSaturation);
	fparams->setNamedConstant("BaseIntensity", this->BaseIntensity);
	fparams->setNamedConstant("BaseSaturation", this->BaseSaturation);
}
