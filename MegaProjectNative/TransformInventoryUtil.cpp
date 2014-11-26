#include "StdAfx.h"
#include "TransformInventoryUtil.h"
#include "GameFramework.h"

template<> TransformInventoryUtil* Ogre::Singleton<TransformInventoryUtil>::msSingleton = 0;

TransformInventoryUtil::TransformInventoryUtil(void)
{
}


TransformInventoryUtil::~TransformInventoryUtil(void)
{
}

Vector3 TransformInventoryUtil::getOriginPositionPlane()
{
	Camera* player_camera = GameFramework::getSingletonPtr()->camera;
	Plane far_plane = player_camera->getFrustumPlane(1);

	float x_percent = 0.5; //((float)x / player_camera->getViewport()->getActualWidth());
	float y_percent = 0.5; //((float)y / player_camera->getViewport()->getActualHeight());

	Ogre::Ray ray = player_camera->getCameraToViewportRay(x_percent, y_percent);

	std::pair<bool, Real> result = ray.intersects(far_plane);

	if (result.first)
	{
		Vector3 origin_plane =  /*ray.getOrigin() + ray.getDirection() * 1000*/ray.getPoint(result.second * 0.9);
		return origin_plane;
	}

	return Vector3::ZERO;
}

void TransformInventoryUtil::update()
{
	
}


