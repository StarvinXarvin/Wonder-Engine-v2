#include "Camera.h"
#include "Globals.h"

#include <glm/ext/matrix_transform.hpp>

Camera::Camera() : fov(60), aspect(4.0/3.0), zNear(0.1), zFar(100), eye(10, 2, 10), center(0, 1, 0), up(0, 1, 0) {}



glm::dmat4 Camera::computeLookAt() const {
	return glm::lookAt(eye, center, up);
}

void Camera::cameraMove(int id) {
	switch (id) {
	case UP:
		center -= yAxis;
		eye -= yAxis;
		break;
	case DOWN:
		center += yAxis;
		eye += yAxis;
		break;
	case LEFT:
		center -= xAxis;
		eye -= xAxis;
		break;
	case RIGHT:
		center += xAxis;
		eye += xAxis;
		break;
		//Va con matrices
		//Para rotar, probar a hacer que rotes con las flechas direccionales moviendo el center, en teoria eso deberia crear la rotacion
	}
}

void Camera::ResetCenter() {
	center = { 0, 1, 0 };
	prevMouseX = 0;
	prevMouseY = 0;
}

void Camera::cameraRotate(double x, double y) {
	if (prevMouseX != 0 && prevMouseY != 0) {
		vec2 mouseDir = { x - prevMouseX, y - prevMouseY };
		//eye.x += mouseDir.x * 0.05;
		//eye.y += mouseDir.y * 0.05;
		LOG("MousePos: x: %f, y: %f", mouseDir.x, mouseDir.y);
		vec3 axisX(glm::normalize(yAxis));
		vec3 axisY(glm::normalize(xAxis));
		float angleX = (0.01f * mouseDir.x);
		float angleY = (0.01f * mouseDir.y);
		RotateCameraAroundObject(center, eye, up, angleY, axisY);
		RotateCameraAroundObject(center, eye, up, angleX, axisX);
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
}

void Camera::CameraZoom(int zoom) {
	vec3 zoomAxis = zAxis;
	zoomAxis *= zoom;
	center -= zoomAxis;
	eye -= zoomAxis;
}

void Camera::computeAxis() {
	zAxis = eye - center;
	//yAxis tiene que ser coplanario al eje y ortonormal y simultaneamente perpendicular a zAxis
	//El determinante de yAxis, zAxis y (0, 1, 0) debe ser 0 + El producto escalar de yAxis y zAxis debe ser 0
	yAxis = vec3f((zAxis.x / zAxis.z), ((-((zAxis.x * zAxis.x) / zAxis.z) - zAxis.z) / zAxis.y), 1);
	xAxis = glm::cross(zAxis, yAxis);
	glm::normalize(zAxis);
	glm::normalize(yAxis);
	glm::normalize(xAxis);
	zAxis *= cameraSpeed*0.35;
	yAxis *= cameraSpeed*0.15;
	xAxis *= cameraSpeed*0.02;
	//xAxis tiene que ser perpendicular a yAxis y a zAxis (Producto vectorial)
}


