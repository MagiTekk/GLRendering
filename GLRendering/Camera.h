#pragma once

// GLM
#include <glm/glm.hpp>

struct GLFWwindow;
typedef unsigned int GLuint;
typedef float GLfloat;

class Camera
{
public:
	Camera();

	void Execute();

private:

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// Window dimensions
	const GLuint WIDTH = 800, HEIGHT = 600;


#pragma region Callbacks (with access to member variables)
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	void SetCallbackFunctions(GLFWwindow* window);

	void MousePositionCallback(GLFWwindow* window, double positionX, double positionY);
	void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	class GLFWCallbackWrapper
	{
	public:
		GLFWCallbackWrapper() = delete;
		GLFWCallbackWrapper(const GLFWCallbackWrapper&) = delete;
		GLFWCallbackWrapper(GLFWCallbackWrapper&&) = delete;
		~GLFWCallbackWrapper() = delete;

		static void MousePositionCallback(GLFWwindow* window, double positionX, double positionY);
		static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void SetApplication(Camera *application);
	private:
		static Camera* s_application;
	};
#pragma endregion
};

