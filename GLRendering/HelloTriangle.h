#pragma once

struct GLFWwindow;
typedef unsigned int GLuint;
typedef char GLchar;

class HelloTriangle
{
public:
	HelloTriangle();
	void Execute();

private:

	// Window dimensions
	const GLuint WIDTH = 800, HEIGHT = 600;

	const GLchar* vertexShaderSource = nullptr;
	const GLchar* fragmentShaderSource = nullptr;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	
};

