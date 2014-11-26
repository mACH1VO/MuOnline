#include "StdAfx.h"
#include "CameraMan.h"
#include "TransformInventoryUtil.h"
#include "GameFramework.h"
#include "InventoryItem.h"

#include "PlayerInventory.h"
#include "StashInventory.h"
#include "ShopInventory.h"

#include "Player.h"

CameraMan::CameraMan(Camera* cam)
{
	this->mCamera = cam;
	this->Factor = 1;
	this->cameraPositionDistance = new Vector3(40, 55, 40);
	this->AutoTrackMainPlayer = true;
	this->mEnabled = false;

	this->mGoingBack = false;
	this->mGoingDown = false;
	this->mGoingForward = false;
	this->mGoingLeft = false;
	this->mGoingRight = false;
	this->mGoingUp = false;
	this->mFastMove = false;

	//this->mCamera = GameFramework::getSingletonPtr()->camera;
}

CameraMan::~CameraMan(void)
{
}

void CameraMan::UpdateCamera(float timeFragment)
{
	if (!mEnabled)
		return;

	if (AutoTrackMainPlayer)
		return;

	// build our acceleration vector based on keyboard input composite
	Vector3 move = Vector3::ZERO;
	if (mGoingForward)
		move += this->mCamera->getDirection();
	if (mGoingBack)
		move -= mCamera->getDirection();
	if (mGoingRight)
		move += mCamera->getRight();
	if (mGoingLeft)
		move -= mCamera->getRight();
	if (mGoingUp)
		move += mCamera->getUp();
	if (mGoingDown)
		move -= mCamera->getUp();

	move.normalise();
	move *= 40; // Natural speed is 150 units/sec.
	if (mFastMove)
		move *= 10; // With shift button pressed, move twice as fast.

	if (move != Vector3::ZERO)
	{
		//mCamera.Move(move * timeFragment);
		this->mCamera->getParentSceneNode()->setPosition( mCamera->getParentSceneNode()->getPosition() + move * timeFragment);

		//this->camera_ortho_tricker->getParentSceneNode()->setPosition( mCamera->getParentSceneNode()->getPosition() );
	}

	
}

void CameraMan::MouseMovement(int x, int y)
{
	if (!mEnabled)
		return;

	if (AutoTrackMainPlayer)
		return;

	float sens = 0.3f;
	mCamera->yaw(Degree(-x * 0.15f) * sens);
	mCamera->pitch(Degree(-y * 0.15f) * sens);

	//update camera tricker!
	//this->camera_ortho_tricker->yaw(Degree(-x * 0.15f) * sens);
	//this->camera_ortho_tricker->pitch(Degree(-y * 0.15f) * sens);
}

void CameraMan::updatePlayertracker(Vector3 pos)
{
	if (this->AutoTrackMainPlayer)
	{
		Factor = 1.4f;

		this->mCamera->getParentSceneNode()->setPosition( pos + *cameraPositionDistance * Factor);
		//this.mCamera.ParentSceneNode.Position = this.mCamera.Position;
		this->mCamera->lookAt(pos);

		//update camera tricker!
		//this->camera_ortho_tricker->getParentSceneNode()->setPosition(this->mCamera->getParentSceneNode()->getPosition());
		//this->camera_ortho_tricker->lookAt(pos);

		Vector3 origin_plane = TransformInventoryUtil::getSingletonPtr()->getOriginPositionPlane();
		int actual_width = GameFramework::getSingletonPtr()->Viewport->getActualWidth();
		int actual_height =  GameFramework::getSingletonPtr()->Viewport->getActualHeight();
		actual_width = actual_width / GameFramework::getSingletonPtr()->FACTOR_INVENTORY_SIZE_POSITION;
		actual_height = actual_height / GameFramework::getSingletonPtr()->FACTOR_INVENTORY_SIZE_POSITION;
		this->camera_ortho_tricker->getParentSceneNode()->setPosition(origin_plane + Vector3((actual_width / 2), ( -actual_height / 2 ), 1000));

		if (GameFramework::getSingletonPtr()->mainPlayer != 0)
		{
			GameFramework::getSingletonPtr()->mainPlayer->inventory->tryRepositionAllItems();
			GameFramework::getSingletonPtr()->mainPlayer->shopInventory->tryRepositionAllItems();
			GameFramework::getSingletonPtr()->mainPlayer->stashInventory->tryRepositionAllItems();
		}

	}

}