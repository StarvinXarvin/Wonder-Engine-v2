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

	mat4 computeLookAt() const;

	void cameraMove(int id);

	void FPSMovement(int id);

	void ResetCenter(int id);

	void MouseRotateAroundObject(double x, double y);

	void RotateCameraAroundObject(vec3& center, vec3& eye, float angleInRadiansX, const glm::vec3& axisX, float angleInRadiansY, const glm::vec3& axisY);

	void MousePointLookAt(double x, double y);

	void RotateCameraFPS(vec3& center, vec3& eye, float angleInRadiansX, const glm::vec3& axisX, float angleInRadiansY, const glm::vec3& axisY);

	void CameraZoom(int zoom);

	void computeAxis();

	void PrintVector(vec3 vector, const char* name);

	Camera();
};

