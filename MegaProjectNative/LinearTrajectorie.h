#pragma once
#include "stdafx.h"

using namespace Ogre;
namespace Utilities
{

class LinearTrajectorie
{
public:
	LinearTrajectorie(Vector3 from, Vector3 to);
	~LinearTrajectorie(void);

	Vector3 V0;
	Vector3 Destination;
	float PathLen;
	Vector3 Versor;
	Vector3 Velocity;
	Vector3 CurrentPosition;
	Vector3 Direction;
	float Speed;

	float CurrentLen;

	Vector3 advance(float elapsed, float speed);
	bool hasReachedPosition();

};

}