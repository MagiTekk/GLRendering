#pragma once

struct GLFWwindow;
typedef unsigned int GLuint;
typedef float GLfloat;


class Transformations
{
public:
	Transformations();

	void Execute();

private:

	// Window dimensions
	const GLuint WIDTH = 800, HEIGHT = 600;

	GLfloat alphaBlend = 0.2f;


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
		static void SetApplication(Transformations *application);
	private:
		static Transformations* s_application;
	};
#pragma endregion
};

