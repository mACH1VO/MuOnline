#pragma once
#include "stdafx.h"

using namespace Ogre;

class GameFramework;

class CameraMan
{
public:
	CameraMan(Camera* cam);
	~CameraMan(void);

public:
	Camera* mCamera;
	Camera *camera_ortho_tricker;

	bool mGoingForward;
	bool mGoingBack;
	bool mGoingRight;
	bool mGoingLeft;
	bool mGoingUp;
	bool mGoingDown;
	bool mFastMove;
	bool mEnabled;

public:
	Vector3* cameraPositionDistance;
	float Factor;
	bool AutoTrackMainPlayer;

	void UpdateCamera(float timeFragment);
	void MouseMovement(int x, int y);
	void updatePlayertracker(Vector3 pos);
};
