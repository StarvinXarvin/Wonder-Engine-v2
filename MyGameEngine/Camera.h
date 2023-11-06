#pragma once

#include "types.h"

class Application;

enum CameraDirection {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD
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

	void ResetCenter(int id);
	void cameraMove(int id);
	void cameraRotate(double x, double y);
	void RotateCameraAroundObject(vec3& center, vec3& eye, vec3& up, float angleInRadians, const glm::vec3& axis);
	void RotateDirection(int id);

	void FPSMovement(int id);

	void MousePointLookAt(double x, double y);

	void RotateCameraAroundItself(vec3& center, vec3& eye, vec3& up, float angleInRadians, const glm::vec3& axis);

	void CameraZoom(int zoom);

	mat4 computeLookAt() const;

	void computeAxis();

	void PrintVector(vec3 vector, const char* name);

	Camera();
};

