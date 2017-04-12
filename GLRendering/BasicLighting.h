#pragma once

// GLM
#include <glm/glm.hpp>
#include "Camera.h"

struct GLFWwindow;
typedef unsigned int GLuint;
typedef float GLfloat;

class BasicLighting
{
public:
	BasicLighting();

	void Execute();

private:

	// Window dimensions
	const GLuint WIDTH = 800, HEIGHT = 600;

	// Time
	GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
	GLfloat lastFrame = 0.0f;  	// Time of last frame

								// Camera
	Camera camera{ glm::vec3(0.0f, 0.0f, 3.0f) };
	GLfloat lastX = static_cast<GLfloat>(WIDTH / 2.0);
	GLfloat lastY = static_cast<GLfloat>(HEIGHT / 2.0);

	// Light attributes - in world coordinates
	//glm::vec3 lightPos{ 1.2f, 1.0f, 2.0f };
	glm::vec3 lightPos{ 0.0f, 0.0f, 0.0f };

	// Movement
	bool keys[1024] = { false };
	GLfloat firstMouse = true;
	void do_movement();


#pragma region Callbacks (with access to member variables)

	void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
	void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	// Sets which callbacks are enabled
	void SetCallbackFunctions(GLFWwindow* window);

	class GLFWCallbackWrapper
	{
	public:
		GLFWCallbackWrapper() = delete;
		GLFWCallbackWrapper(const GLFWCallbackWrapper&) = delete;
		GLFWCallbackWrapper(GLFWCallbackWrapper&&) = delete;
		~GLFWCallbackWrapper() = delete;

		static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MousePositionCallback(GLFWwindow* window, double positionX, double positionY);
		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void SetApplication(BasicLighting *application);
	private:
		static BasicLighting* s_application;
	};
#pragma endregion

};

