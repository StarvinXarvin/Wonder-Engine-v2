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
	vec3 xAxis;
	vec3 yAxis;
	vec3 zAxis;

	float cameraSpeed = 0.1f;

	void cameraMove(int id);

	void CameraZoom(int zoom);

	mat4 computeLookAt() const;

	void computeAxis();

	Camera();
};

