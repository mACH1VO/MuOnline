#include "StdAfx.h"
#include "BlurListener.h"

using namespace Ogre;

BlurListener::BlurListener(void)
{
	fuzziness = 5;
}


BlurListener::~BlurListener(void)
{
}

void BlurListener::notifyViewportSize(int width, int height)
{

}
//---------------------------------------------------------------------------
void BlurListener::notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	mat->load();
	/*Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();
	fparams->setNamedConstant("radius", 10);
	fparams->setNamedConstant("intensity", 1);*/

}
float BlurListener::GaussianDistribution( float x, float y, float rho )
{
	float g = 1.0f / Ogre::Math::Sqr( 2.0f * Ogre::Math::PI * rho * rho );
	g *= Ogre::Math::Exp( -( x * x + y * y ) / ( 2.0f * rho * rho ) );
	return g;
}
//---------------------------------------------------------------------------
void BlurListener::notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat)
{
	Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();
	if( pass_id == 700 || pass_id == 701 )
	{
		bool horizontal = pass_id == 700;

		Ogre::Vector2 sampleOffsets[15];
		Ogre::Vector4 sampleWeights[15];

		// calculate gaussian texture offsets & weights
		Ogre::Vector2 textureSize = Vector2(1280,720);
		float texelSize = 1.0f / (float)( horizontal ? textureSize.x : textureSize.y );

		texelSize *= fuzziness;

		// central sample, no offset
		sampleOffsets[ 0 ] = Vector2::ZERO;
		{
			float distribution = GaussianDistribution( 0, 0, 3 );
			sampleWeights[ 0 ] = Ogre::Vector4( distribution, distribution, distribution, 0 );
		}

		// 'pre' samples
		for( int n = 1; n < 8; n++ )
		{
			float distribution = GaussianDistribution( n, 0, 3 );
			sampleWeights[ n ] = Vector4( distribution, distribution, distribution, 1 );

			if( horizontal )
				sampleOffsets[ n ] = Vector2( (float)n * texelSize, 0 );
			else
				sampleOffsets[ n ] = Vector2( 0, (float)n * texelSize );
		}
		// 'post' samples
		for( int n = 8; n < 15; n++ )
		{
			sampleWeights[ n ] = sampleWeights[ n - 7 ];
			sampleOffsets[ n ] = -sampleOffsets[ n - 7 ];
		}

		//convert to Vec4 array
		Vector4 vec4Offsets [15];
		for( int n = 0; n < 15; n++ )
		{
			Vector2 offset = sampleOffsets[ n ];
			vec4Offsets[ n ] = Vector4( offset.x, offset.y, 0, 0 );
		}

		Ogre::GpuProgramParametersSharedPtr fparams = mat->getBestTechnique()->getPass(0)->getFragmentProgramParameters();

		//fparams->setNamedConstant( "sampleOffsets", vec4Offsets );
		//fparams->setNamedConstant( "sampleWeights", sampleWeights );
	}
}
