#pragma once

struct GLFWwindow;
typedef unsigned int GLuint;

class Textures
{
public:
	Textures();

	void Execute();

private:

	// Window dimensions
	const GLuint WIDTH = 800, HEIGHT = 600;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

