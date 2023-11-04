#pragma once

#include "types.h"

class Application;

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

	int prevMouseX;
	int prevMouseY;
	int mouseX;
	int mouseY;

	float cameraSpeed = 0.1f;

	void ResetCenter();
	void cameraMove(int id);
	void cameraRotate(double x, double y);

	void CameraZoom(int zoom);

	mat4 computeLookAt() const;

	void computeAxis();

	Camera();
};

