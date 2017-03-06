#pragma once
#include <GLFW/glfw3.h>

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
	
	GLfloat alphaBlend;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

