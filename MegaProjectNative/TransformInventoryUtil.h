#pragma once
#include "stdafx.h"

using namespace Ogre;
class TransformInventoryUtil: public Ogre::Singleton<TransformInventoryUtil>
{
public:
	TransformInventoryUtil(void);
	~TransformInventoryUtil(void);

	Vector3 cameraPosition;
	Vector3 startPlanePoint_0_0;
	Vector3 getOriginPositionPlane();
	void update();
};

