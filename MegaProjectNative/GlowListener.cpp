#include "StdAfx.h"
#include "GlowListener.h"


GlowListener::GlowListener(void)
{
	this->mBlackMat = Ogre::MaterialManager::getSingleton().create("mGlowBlack", "Internal");
	this->mBlackMat->getTechnique(0)->getPass(0)->setDiffuse(0,0,0,0);
	this->mBlackMat->getTechnique(0)->getPass(0)->setSpecular(0,0,0,0);
	this->mBlackMat->getTechnique(0)->getPass(0)->setAmbient(0,0,0);
	this->mBlackMat->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,0);
}


GlowListener::~GlowListener(void)
{
}

void GlowListener::notifyViewportSize(int width, int height)
{

}
//---------------------------------------------------------------------------
void GlowListener::notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	mat->load();
	/*Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();
	fparams->setNamedConstant("radius", 10);
	fparams->setNamedConstant("intensity", 1);*/

}
//---------------------------------------------------------------------------
void GlowListener::notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	/*Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();
	fparams->setNamedConstant("GloomIntensity", this->GloomIntensity);
	fparams->setNamedConstant("GloomSaturation", this->GloomSaturation);
	fparams->setNamedConstant("BaseIntensity", this->BaseIntensity);
	fparams->setNamedConstant("BaseSaturation", this->BaseSaturation);*/
}
