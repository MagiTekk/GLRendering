#pragma once

struct GLFWwindow;
typedef unsigned int GLuint;
typedef char GLchar;

class TwoTriangles
{
public:
	TwoTriangles();
	~TwoTriangles();

	void Execute();

private:

	// Window dimensions
	const GLuint WIDTH = 800, HEIGHT = 600;

	const GLchar* vertexShaderSource = nullptr;
	const GLchar* fragmentShaderSource = nullptr;
	const GLchar* fragmentShaderYellowSource = nullptr;
	const GLchar* fragmentShaderGreenSource = nullptr;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

