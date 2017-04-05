#pragma once

// GLM
#include <glm/glm.hpp>

struct GLFWwindow;
typedef unsigned int GLuint;
typedef float GLfloat;

enum class Direction
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


class Camera
{
public:
	Camera();
	~Camera();

	GLfloat Zoom;

	void SetCameraPos(glm::vec3 _cameraPos);
	void ProcessKeyboard(Direction _dir, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);
	void ProcessMouseScroll(GLfloat yoffset);
	glm::mat4 GetViewMatrix() const;

private:

	// declare our pitch and yaw values
	GLfloat pitch = 0.0f;

	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Euler angles work) so we initially rotate a bit to the left.
	GLfloat yaw = -90.0f;

	// field of view
	GLfloat fov = 45.0f;

	// Declare the camera position
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
};

