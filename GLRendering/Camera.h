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

	// storing the keys that are pressed so that we can move around while key is pressed
	bool keys[1024] = {false};
	void do_movement();
	GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
	GLfloat lastFrame = 0.0f;  	// Time of last frame
	
	// Mouse calculations for the camera movement
	// Center of the screen
	GLfloat lastX = WIDTH / 2.0;
	GLfloat lastY = HEIGHT / 2.0;
	// declare our pitch and yaw values
	GLfloat pitch = 0.0f;
	GLfloat yaw = -90.0f; // Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Euler angles work) so we initially rotate a bit to the left.
	GLfloat firstMouse = true;


	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// Window dimensions
	const GLuint WIDTH = 800, HEIGHT = 600;


#pragma region Callbacks (with access to member variables)
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	void SetCallbackFunctions(GLFWwindow* window);

	void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
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

