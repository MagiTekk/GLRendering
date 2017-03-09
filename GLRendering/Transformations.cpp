#include "Transformations.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// SOIL
#include <SOIL/SOIL.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include <iostream>
#include "Shader.h"


Transformations::Transformations()
{
}

void Transformations::Execute()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GLRendering", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//-- Input Binding
	SetCallbackFunctions(window);

	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// Shader Program
	Shader ShaderProgram("../Shaders/ColoredShader.vert", "../Shaders/ColoredShader.frag");

	GLfloat vertices[] = {
		// Positions          // Colors
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,		// Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,		// Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,		// Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,		// Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Our Rectangle
	glBindVertexArray(VAO);
	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Unbind VAO
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwPollEvents();

		// ** Rendering commands here **
		#pragma region Rendering commands

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use compiled program
		ShaderProgram.Use();

		// Draw the rectangle
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); // Unbind VAO

		#pragma endregion

							  // Swap the buffers
		glfwSwapBuffers(window);
	}

	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}

#pragma region Callbacks (with access to member variables)
void Transformations::SetCallbackFunctions(GLFWwindow* window)
{
	GLFWCallbackWrapper::SetApplication(this);
	glfwSetCursorPosCallback(window, GLFWCallbackWrapper::MousePositionCallback);
	glfwSetKeyCallback(window, GLFWCallbackWrapper::KeyboardCallback);
}

Transformations* Transformations::GLFWCallbackWrapper::s_application = nullptr;

void Transformations::MousePositionCallback(GLFWwindow* window, double positionX, double positionY)
{

}

void Transformations::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// closing the application
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}

void Transformations::GLFWCallbackWrapper::MousePositionCallback(GLFWwindow* window, double positionX, double positionY)
{
	s_application->MousePositionCallback(window, positionX, positionY);
}

void Transformations::GLFWCallbackWrapper::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	s_application->KeyboardCallback(window, key, scancode, action, mods);
}

void Transformations::GLFWCallbackWrapper::SetApplication(Transformations *application)
{
	GLFWCallbackWrapper::s_application = application;
}
#pragma endregion
