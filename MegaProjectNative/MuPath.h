#pragma once
#include "stdafx.h"

namespace Utilities
{

class LinearTrajectorie;

class MuPath
{
public:

	std::vector<Ogre::Vector3>* points;
	std::vector<LinearTrajectorie*>* _linearTrajectories;

	LinearTrajectorie* CurrentLinearTrajectorie;
	Ogre::Vector3 CurrDirection;

	float CurrentTotalLen; 
	float CurrentLocalLen; 
	float TotalLen; 
	float currentLinearTrajectorieIndex;

	bool HasReachedPosition();
	Vector3 Advance(float elapsed, float translateSpeed);


	MuPath(std::vector<Ogre::Vector3> _vertices);
	~MuPath(void);
};

}