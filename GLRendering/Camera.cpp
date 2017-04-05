#include "Camera.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include <iostream>

Camera::Camera()
{
	// Init Zoom
	Zoom = glm::radians(fov);
}

Camera::~Camera()
{
}

void Camera::SetCameraPos(glm::vec3 _cameraPos)
{
	cameraPos = _cameraPos;
}


void Camera::ProcessKeyboard(Direction _dir, GLfloat deltaTime)
{
	// Camera controls
	GLfloat cameraSpeed = 5.0f * deltaTime;
	glm::vec3 fpsCameraFront = glm::vec3(cameraFront.x, 0.0f, cameraFront.z);
	if (_dir == Direction::FORWARD)
		cameraPos += cameraSpeed * fpsCameraFront;	// use cameraFront to "fly"
	if (_dir == Direction::BACKWARD)
		cameraPos -= cameraSpeed * fpsCameraFront;	// use cameraFront to "fly"
	if (_dir == Direction::LEFT)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (_dir == Direction::RIGHT)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset)
{
	GLfloat sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// constrain our pitch so that the user cannot invert the camera
	// after 90 degrees the camera rotates and makes a weird behavior
	// we don't need to constrain our yaw since we want to be able to turn around
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	// Calculate the actual direction vector from the resulting yaw and pitch value
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}

void Camera::ProcessMouseScroll(GLfloat yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
	{
		fov -= yoffset;
	}
	if (fov <= 1.0f)
	{
		fov = 1.0f;
	}
	if (fov >= 45.0f)
	{
		fov = 45.0f;
	}

	// Update Zoom
	Zoom = glm::radians(fov);
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
