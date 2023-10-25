#pragma once

#include "types.h"

enum CameraDirection {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	ZOOMIN,
	ZOOMOUT
};

struct Camera
{
	double fov;
	double aspect;
	double zNear;
	double zFar;

	vec3 eye;
	vec3 center;
	vec3 up;

	int cameraSpeed = 1;

	void cameraMove(int id);

	mat4 computeLookAt() const;

	Camera();
};

