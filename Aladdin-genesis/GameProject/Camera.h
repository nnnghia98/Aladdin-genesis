﻿#ifndef _CAMERA_H
#define _CAMERA_H

#include <d3dx9.h>

namespace cameraNS {
	const int marginLeft = 60;
	const int marginRight = 130;
	const int marginVertical = 60;
	const int marginWhenJump = 10;
	const int marginWhenGlance = 133;
	const int marginWhenSit = -60;
}

class Camera
{
private:
	float XCamera;
	float YCamera;

	float boundaryLeft; //biên giới hạn bên trái
	float boundaryRight; //biên giới hạn bên phải

public:
	Camera();
	~Camera();

	void setPositionCam(float x, float y);
	float getXCamera() { return XCamera; }
	float getYCamera() { return YCamera; }

	void setBoundary(float bLeft, float bRight);
	float getBoundaryLeft() { return boundaryLeft; }
	float getBoundaryRight() { return boundaryRight; }

	D3DXVECTOR2 CameraTransform(float xWorld, float yWorld);
};

#endif