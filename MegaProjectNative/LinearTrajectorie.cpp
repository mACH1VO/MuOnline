#include "StdAfx.h"
#include "LinearTrajectorie.h"

using namespace Ogre;

namespace Utilities
{

LinearTrajectorie::LinearTrajectorie(Vector3 from, Vector3 to)
{
	//Logger.Add("Speed " + speed.ToString());
	V0 = from;
	Destination = to;
	Versor = (to - from).normalisedCopy();
	Direction = Versor;
	PathLen = (to - from).length();
	CurrentLen = 0;
	CurrentPosition = from;
}


LinearTrajectorie::~LinearTrajectorie(void)
{
}

Vector3 LinearTrajectorie::advance(float elapsed, float speed)
{
	//Logger.Add("Factor " + (ticks / 100000f).ToString());

	this->Speed = speed;
	this->Velocity = (Versor * speed); //actualize current velocity with speed sended

	Vector3 newPosition = CurrentPosition + Velocity * elapsed;

	CurrentLen += (newPosition - CurrentPosition).length(); //( new - old ).len, o sea, suma de a pedacitos avanzados

	CurrentPosition = newPosition;
	return CurrentPosition;

}

bool LinearTrajectorie::hasReachedPosition()
{
	if (CurrentLen >= PathLen)
		return true;
	return false;
}

}