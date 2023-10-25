#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>

Camera::Camera() : fov(60), aspect(4.0/3.0), zNear(0.1), zFar(100), eye(10, 2, 10), center(0, 1, 0), up(0, 1, 0) {}



glm::dmat4 Camera::computeLookAt() const {
	return glm::lookAt(eye, center, up);
}

void Camera::cameraMove(int id) {
	switch (id) {
	case UP:
		center.y += cameraSpeed;
		eye.y += cameraSpeed;
		break;
	case DOWN:
		center.y -= cameraSpeed;
		eye.y -= cameraSpeed;
		break;
	case LEFT:
		center.x -= cameraSpeed;
		eye.x -= cameraSpeed;
		break;
	case RIGHT:
		center.x += cameraSpeed;
		eye.x += cameraSpeed;
		break;
	case ZOOMIN:
		center.z -= cameraSpeed;
		eye.z -= cameraSpeed;
		break;
	case ZOOMOUT:
		center.z += cameraSpeed;
		eye.z += cameraSpeed;
		break;

		//Va con matrices
	}
}

void Camera::computeAxis() {
	vec3f zAxis = eye - center;
	//yAxis tiene que ser coplanario al eje y ortonormal y simultaneamente perpendicular a zAxis
	//El determinante de yAxis, zAxis y (0, 1, 0) debe ser 0 + El producto escalar de yAxis y zAxis debe ser 0
	vec3f yAxis = vec3f((zAxis.x / zAxis.z), ((-((zAxis.x * zAxis.x) / zAxis.z) - zAxis.z) / zAxis.y), 1);
	//vec3f xAxis = yAxis.

	//xAxis tiene que ser perpendicular a yAxis y a zAxis (Producto vectorial)
}


