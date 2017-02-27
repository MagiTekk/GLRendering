#include "TwoTriangles.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other includes
#include <iostream>
#include <chrono>

TwoTriangles::TwoTriangles()
{

#pragma region Shaders

	/* Creating a very basic Vertex Shader using GLSL (OpenGL Shading Language)
	* The current vertex shader is probably the most simple vertex shader we can imagine
	* because we did no processing whatsoever on the input data and simply forwarded it to the shader's output
	*/
	vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"in vec3 color;\n"
		"out vec3 Color;\n"
		"void main()\n"
		"{\n"
		"Color = color;\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\0";

	fragmentShaderSource = "#version 330 core \n"
		//"uniform vec3 drawingColor;\n"
		"in vec3 Color;\n"
		"out vec4 outColor;\n"
		"void main()\n"
		"{\n"
		"outColor = vec4(Color, 1.0f);\n"
		"}\0";

	fragmentShaderYellowSource = "#version 330 core \n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 0.9f, 0.2f, 1.0f);\n"
		"}\0";

	fragmentShaderGreenSource = "#version 330 core \n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(0.1f, 1.0f, 0.1f, 1.0f);\n"
		"}\0";

#pragma endregion Shaders

}


TwoTriangles::~TwoTriangles()
{
}

void TwoTriangles::Execute()
{
	//auto t_start = std::chrono::high_resolution_clock::now();
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;

	// We create the main function where we will instantiate the GLFW window
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Next we're required to create a window object. This window object holds all the windowing data and is used quite frequently by GLFW's other functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GLRendering", nullptr, nullptr);

	// Tell GLFW to make the context of our window the main context on the current thread
	glfwMakeContextCurrent(window);

	// We register the callback functions after we've created the window and before the game loop is initiated
	glfwSetKeyCallback(window, key_callback);

	// GLEW manages function pointers for OpenGL so we want to initialize GLEW before we call any OpenGL functions
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// We have to tell OpenGL the size of the rendering window so OpenGL knows how we want to display the data and coordinates with respect to the window
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	// We can set those dimensions via the glViewport function
	glViewport(0, 0, width, height);

	// Build and compile our shader program
#pragma region VertexShader

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

#pragma endregion VertexShader

#pragma region FragmentShader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

#pragma endregion FragmentShader

#pragma region FragmentShaderYellow

	GLuint fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderYellowSource, NULL);
	glCompileShader(fragmentShaderYellow);

	// Check for compile time errors
	glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::YELLOW::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

#pragma endregion FragmentShaderYellow

#pragma region FragmentShaderGreen

	GLuint fragmentShaderGreen = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderGreen, 1, &fragmentShaderGreenSource, NULL);
	glCompileShader(fragmentShaderGreen);

	// Check for compile time errors
	glGetShaderiv(fragmentShaderGreen, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderGreen, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::GREEN::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

#pragma endregion FragmentShaderGreen

#pragma region LinkShaders

	GLuint shaderProgram = glCreateProgram();

	// Link shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	GLuint shaderProgramYellow = glCreateProgram();

	// Link shaders to the shader program
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	// Check for linking errors
	glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::YELLOW::LINKING_FAILED\n" << infoLog << std::endl;
	}

	GLuint shaderProgramGreen = glCreateProgram();

	// Link shaders to the shader program
	glAttachShader(shaderProgramGreen, vertexShader);
	glAttachShader(shaderProgramGreen, fragmentShaderGreen);
	glLinkProgram(shaderProgramGreen);

	// Check for linking errors
	glGetProgramiv(shaderProgramGreen, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramGreen, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::GREEN::LINKING_FAILED\n" << infoLog << std::endl;
	}

#pragma endregion

	// delete the shader objects once we've linked them into the program object; we no longer need them anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShaderYellow);
	glDeleteShader(fragmentShaderGreen);

#pragma region Triangles

	GLfloat firstTriangle[] = {
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,		// Top Right - Red
		0.5f, -0.45f, 0.0f, 0.0f, 1.0f, 0.0f,		// Bottom Right - Green
		-0.45f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f		// Top Left - Blue
	};

	GLfloat secondTriangle[] = {
		-0.5f,  0.45f, 0.0f, 0.0f, 1.0f, 0.0f,	// Top Left - Green
		0.45f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	// Bottom Right - Red
		-0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f	// Bottom Left - Blue
	};

	GLuint VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);	// Since these objects are now arrays, we can omit the reference to their address
	glGenBuffers(2, VBOs);

	
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");

	//FirstTriangle
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glEnableVertexAttribArray(posAttrib);
	glEnableVertexAttribArray(colAttrib);
	// The fifth parameter is set to 6 * sizeof(float) now, because each vertex consists of 6 floating point attribute values.
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	// The offset of 3*sizeof(float) for the color attribute is there because each vertex starts with 3 floating point values for the position that it has to skip over.
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	//SecondTriangle
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glEnableVertexAttribArray(posAttrib);
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

#pragma endregion SecondTriangle
#pragma endregion Triangles

	// Uncommenting this call will result in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwPollEvents();

		// Rendering commands here

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Change the color of our fragment shader by setting the uniform
		//auto t_now = std::chrono::high_resolution_clock::now();
		//float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

		//GLint uniColor = glGetUniformLocation(shaderProgram, "drawingColor");
		//glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
		//glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);

		// Use compiled program
		glUseProgram(shaderProgram);

		//glUseProgram(shaderProgramYellow);	// use a different shader for the color

		// Draw the first triangle
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0); // Unbind VAO

		//glUseProgram(shaderProgramGreen);		// use a different shader for the color

		// Change the color of our fragment shader by setting the uniform
		//glUniform3f(uniColor, 0.0f, 1.0f, 0.0f);
		//glUniform3f(uniColor, 0.0f, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f);

		// Draw the second triangle
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0); // Unbind VAO

		// Swap the buffers
		glfwSwapBuffers(window);
	}

	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}

void TwoTriangles::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, 
	// closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
