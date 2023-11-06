#include "Camera.h"
#include "Globals.h"
#include "WonderEngine.h"

#include <glm/ext/matrix_transform.hpp>

Camera::Camera() : fov(60), aspect(4.0/3.0), zNear(0.1), zFar(100), eye(10, 2, 10), center(0, 1, 0), up(0, 1, 0) {}



glm::dmat4 Camera::computeLookAt() const {
	return glm::lookAt(eye, center, up);
}

void Camera::cameraMove(int id) {
	computeAxis();
	switch (id) {
	case UP:
		center -= yAxis;
		eye -= yAxis;
		//LOG("Y axis: (%f, %f, %f)", yAxis.x, yAxis.y, yAxis.z);
		break;
	case DOWN:
		center += yAxis;
		eye += yAxis;
		//LOG("Y axis: (%f, %f, %f)", yAxis.x, yAxis.y, yAxis.z);
		break;
	case LEFT:
		center -= xAxis;
		eye -= xAxis;
		//LOG("X axis: (%f, %f, %f)", xAxis.x, xAxis.y, xAxis.z);
		break;
	case RIGHT:
		center += xAxis;
		eye += xAxis;
		//LOG("X axis: (%f, %f, %f)", xAxis.x, xAxis.y, xAxis.z);
		break;
		//Va con matrices
		//Para rotar, probar a hacer que rotes con las flechas direccionales moviendo el center, en teoria eso deberia crear la rotacion

		//Problema a arreglar: Cuando el axis calculado para x tiene mayor componente x, la camara se mueve mas rapido en direccion x (duh) eso hay que arreglarlo
	}
}

void Camera::RotateDirection(int id) {
	switch (id) {
	case UP:
		RotateCameraAroundObject(center, eye, up, 0.1f, vec3(1.0f, 0.0f, 0.0f));
		break;
	case DOWN:
		RotateCameraAroundObject(center, eye, up, -0.1f, vec3(1.0f, 0.0f, 0.0f));
		break;
	case LEFT:
		RotateCameraAroundObject(center, eye, up, -0.1f, vec3(0.0f, 1.0f, 0.0f));
		break;
	case RIGHT:
		RotateCameraAroundObject(center, eye, up, 0.1f, vec3(0.0f, 1.0f, 0.0f));
		break;
	case FORWARD:
		RotateCameraAroundObject(center, eye, up, 0.1f, vec3(0.0f, 0.0f, 1.0f));
		break;
	case BACKWARD:
		RotateCameraAroundObject(center, eye, up, -0.1f, vec3(0.0f, 0.0f, 1.0f));
		break;
	}
	
}

void Camera::FPSMovement(int id) {
	switch (id) {
	case FORWARD:
		center -= zAxis;
		eye -= zAxis;
		break;
	case BACKWARD:
		center += zAxis;
		eye += zAxis;
		break;
	case LEFT:
		center -= xAxis;
		eye -= xAxis;
		break;
	case RIGHT:
		center += xAxis;
		eye += xAxis;
		break;
	}
}

void Camera::ResetCenter(int id) {
	if (id == 0) {
		center = { 0, 1, 0 };
	}
	prevMouseX = 0;
	prevMouseY = 0;
}

void Camera::cameraRotate(double x, double y) {

	if (prevMouseX != 0 && prevMouseY != 0) {
		vec2 mouseDir = { x - prevMouseX, y - prevMouseY };
		float angleX = (0.01f * mouseDir.x);
		float angleY = (0.01f * mouseDir.y);
		RotateCameraAroundObject(center, eye, up, angleY, -xAxis);
		RotateCameraAroundObject(center, eye, up, angleX, yAxis);
	}
	prevMouseX = x;
	prevMouseY = y;
}

void Camera::RotateCameraAroundObject(vec3& center, vec3& eye, vec3& up, float angleInRadians, const glm::vec3& axis) {
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angleInRadians, axis);
	vec3 translatedEye = eye - center;
	vec3 rotatedEye = vec3(rotation * vec4(translatedEye, 1.0f));
	eye = rotatedEye + center;
	up = glm::mat3(rotation) * up;
	//PrintVector(up, "up");
}

void Camera::MousePointLookAt(double x, double y) {
	if (prevMouseX != 0 && prevMouseY != 0) {
		vec2 mouseDir = { x - prevMouseX, y - prevMouseY };
		float angleX = (0.01f * mouseDir.x);
		float angleY = (0.01f * mouseDir.y);
		RotateCameraAroundItself(center, eye, up, angleY, -xAxis);
		RotateCameraAroundItself(center, eye, up, angleX, yAxis);
	}
	prevMouseX = x;
	prevMouseY = y;
	computeAxis();
}

void Camera::RotateCameraAroundItself(vec3& center, vec3& eye, vec3& up, float angleInRadians, const glm::vec3& axis) {
	mat4 rotation = rotate(glm::mat4(1.0f), angleInRadians, axis);
	center -= eye;
	center = glm::mat3(rotation) * center;
	center += eye;
	up = glm::mat3(rotation) * up;
}

void Camera::CameraZoom(int zoom) {
	vec3 zoomAxis = zAxis;
	zoomAxis *= zoom;
	center -= zoomAxis;
	eye -= zoomAxis;
}

void Camera::computeAxis() {
	zAxis = normalize(eye - center);
	xAxis = normalize(cross(up, zAxis));
	yAxis = normalize(cross(xAxis, zAxis));
	zAxis *= cameraSpeed;
	xAxis *= cameraSpeed;
	yAxis *= cameraSpeed;
}

void Camera::PrintVector(vec3 vector, const char* name) {
	//LOG("%s vector: (%f, %f, %f)", name, vector.x, vector.y, vector.z);
}