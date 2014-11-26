#include "StdAfx.h"
#include "LinearTrajectorie.h"
#include "MuPath.h"

namespace Utilities
{

MuPath::MuPath(std::vector<Ogre::Vector3> _vertices)
{
	this->points = new std::vector<Ogre::Vector3>(_vertices.begin(), _vertices.end());
	this->_linearTrajectories = new std::vector<LinearTrajectorie*>();
	this->TotalLen = 0;
	this->CurrentTotalLen = 0;

	for (int i = 0; i < points->size() - 1; i++)
	{
		LinearTrajectorie* lt = new LinearTrajectorie(points->at(i), points->at(i + 1));
		this->_linearTrajectories->push_back(lt);
		this->TotalLen = this->TotalLen + lt->PathLen;
	}
	this->CurrentLinearTrajectorie = this->_linearTrajectories->at(0);
	this->currentLinearTrajectorieIndex = 0;
	//this->HasChangeDirectionInLastStep = true; //default*/
}


MuPath::~MuPath(void)
{
	delete this->points;

	std::vector<LinearTrajectorie*>::iterator it;

	for (it = this->_linearTrajectories->begin(); it != this->_linearTrajectories->end(); ++it	)
	{
		LinearTrajectorie* curr = *it;
		delete curr;
	}
	delete this->_linearTrajectories;

}

bool MuPath::HasReachedPosition()
{
	return this->CurrentTotalLen >= this->TotalLen; 
}

Vector3 MuPath::Advance(float elapsed, float translateSpeed)
{
	Vector3 retPosition = this->CurrentLinearTrajectorie->advance(elapsed, translateSpeed);
	this->CurrDirection = this->CurrentLinearTrajectorie->Direction;

	if (this->CurrentLinearTrajectorie->hasReachedPosition())
	{
		//this->HasChangeDirectionInLastStep = true;
		if (currentLinearTrajectorieIndex + 1 < this->_linearTrajectories->size())
		{
			//si tiene un trajectrorie adelante, entonces avanza al siguiente y le pega el len que se paso
			float LargoQueSePaso = this->CurrentLinearTrajectorie->CurrentLen - this->CurrentLinearTrajectorie->PathLen;
			this->CurrentTotalLen = this->CurrentTotalLen + this->CurrentLinearTrajectorie->PathLen + LargoQueSePaso;
			this->CurrentLinearTrajectorie = this->_linearTrajectories->at(++currentLinearTrajectorieIndex);
			this->CurrentLinearTrajectorie->CurrentLen = LargoQueSePaso;
			retPosition = this->CurrentLinearTrajectorie->V0 + this->CurrentLinearTrajectorie->Versor * this->CurrentLinearTrajectorie->CurrentLen;

		}
		else
		{
			//no trajectorie adelante, llega al final y listo
			retPosition = this->CurrentLinearTrajectorie->Destination;
			this->CurrentTotalLen = this->TotalLen;
		}
	}

	return retPosition;
}

}
