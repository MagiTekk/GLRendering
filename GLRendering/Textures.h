#pragma once
//#include <GLFW/glfw3.h>
#include <functional>

struct GLFWwindow;
typedef unsigned int GLuint;
typedef float GLfloat;


// http://stackoverflow.com/questions/7676971/pointing-to-a-function-that-is-a-class-member-glfw-setkeycallback

class Textures
{
public:
	Textures();

	void Execute();

private:

	// Window dimensions
	const GLuint WIDTH = 800, HEIGHT = 600;
	
	GLfloat alphaBlend = 0.2f;

	//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

/*------------- CALLBACKS (with access to member variables) ---------------*/
#pragma region Callbacks
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
		static void SetApplication(Textures *application);
	private:
		static Textures* s_application;
	};
#pragma endregion
};