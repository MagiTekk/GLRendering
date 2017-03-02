#include "Textures.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// SOIL
#include <SOIL/SOIL.h>

// Other includes
#include <iostream>
#include "Shader.h"

Textures::Textures()
{
}

void Textures::Execute()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GLRendering", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//-- Input Binding
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Shader Program
	Shader ShaderProgram("../Shaders/ColoredTextureShader.vert", "../Shaders/ColoredTextureShader.frag");

	GLfloat rectangleShape[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	#pragma region Texture mapping

	/*
	We specify 3 texture coordinate points for the triangle.
	We want the bottom-left side of the triangle to correspond with the bottom-left side of the texture so we use the (0,0) texture coordinate for the triangle's bottom-left vertex.
	The same applies to the bottom-right side with a (1,0) texture coordinate. The top of the triangle should correspond with the top-center of the texture image so we take (0.5,1.0) as its texture coordinate.
	We only have to pass 3 texture coordinates to the vertex shader, which then passes those to the fragment shader that neatly interpolates all the texture coordinates for each fragment.
	*/

	GLfloat texCoords[] = {
		0.0f, 0.0f,  // Lower-left corner  
		1.0f, 0.0f,  // Lower-right corner
		0.5f, 1.0f   // Top-center corner
	};

	//--Texture Wrapping

	/*	GL texture options
	- GL_REPEAT: The default behavior for textures. Repeats the texture image.
	- GL_MIRRORED_REPEAT: Same as GL_REPEAT but mirrors the image with each repeat.
	- GL_CLAMP_TO_EDGE: Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
	- GL_CLAMP_TO_BORDER: Coordinates outside the range are now given a user-specified border color
	*/

	// The coordinate axis are "s", "t" (and "r" if you're using 3D textures) equivalent to "x", "y", "z"
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// if we were to use GL_CLAMP_TO_BORDER we need to specify a border color
	// float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	//--Texture Filtering

	// Texture filtering can be set for magnifying and minifying operations (when scaling up or downwards)
	// So you could for example use nearest neighbor filtering (GL_NEAREST) when textures are scaled downwards and linear filtering (GL_LINEAR) for upscaled textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//--Mipmaps

	/* Filtering Mipmaps
	- GL_NEAREST_MIPMAP_NEAREST: takes the nearest mipmap to match the pixel size and uses nearest neighbor interpolation for texture sampling.
	- GL_LINEAR_MIPMAP_NEAREST: takes the nearest mipmap level and samples using linear interpolation.
	- GL_NEAREST_MIPMAP_LINEAR: linearly interpolates between the two mipmaps that most closely match the size of a pixel and samples via nearest neighbor interpolation.
	- GL_LINEAR_MIPMAP_LINEAR: linearly interpolates between the two closest mipmaps and samples the texture via linear interpolation.
	*/

	/*
	A common mistake is to set one of the mipmap filtering options as the magnification filter. 
	This doesn't have any effect since mipmaps are primarily used for when textures get downscaled: 
	texture magnification doesn't use mipmaps and giving it a mipmap filtering option will generate an OpenGL GL_INVALID_ENUM error code.
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // We don't need to apply filtering for magnifying the mipmap, this is a common misuse and leads to errors

	// Loading an image with SOIL
	int textWidth, textHeight;
	unsigned char* image = SOIL_load_image("Content/Textures/container.jpg", &textWidth, &textHeight, 0, SOIL_LOAD_RGB);

	GLuint texture;
	glGenTextures(1, & texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textWidth, textHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// After we're done generating the texture and its corresponding mipmaps, it is good practice to free the image memory and unbind the texture object
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	#pragma endregion

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);	// Since these objects are now arrays, we can omit the reference to their address
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Our Rectangle
	glBindVertexArray(VAO);
	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleShape), rectangleShape, GL_STATIC_DRAW);
	// Bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleShape), rectangleShape, GL_STATIC_DRAW);
	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	// Binding the texture using our sampler to set the color of our rectangle
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Uncommenting this call will result in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwPollEvents();

		// ** Rendering commands here **
	#pragma region Rendering commands

		// Clear the colorbuffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Use compiled program
		ShaderProgram.Use();

		// xOffset using an uniform
		//GLint uniXOffset = glGetUniformLocation(ShaderProgram.Program, "ourTexture");
		//glUniform1f(uniXOffset, 0.5f);
		// OR
		/*GLfloat offset = 0.5f;
		glUniform1f(glGetUniformLocation(ShaderProgram.Program, "xOffset"), offset);*/

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

void Textures::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, 
	// closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
