#include "LightingMaps.h"

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
#include "Camera.h"

LightingMaps::LightingMaps()
{
}

void LightingMaps::Execute()
{
	//GLfloat startTime = static_cast<GLfloat>(glfwGetTime());

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GLRendering", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//-- Input Binding
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	SetCallbackFunctions(window);

	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);

	// Shader Program
	Shader lightingShader("Content/Shaders/LightningMaps.vert", "Content/Shaders/LightningMaps.frag");
	Shader lampShader("Content/Shaders/Lamp.vert", "Content/Shaders/Lamp.frag");

	GLfloat vertices[] = {
		// Positions		  // Normals		   // Texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	// First, set the container's VAO (and VBO)
	GLuint VBO, containerVAO;
	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(containerVAO);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Load textures
    GLuint diffuseMap, specularMap;
    glGenTextures(1, &diffuseMap);
    glGenTextures(1, &specularMap);
    int width, height;
    unsigned char* image;
    // Diffuse map
    image = SOIL_load_image("Content/Textures/container2.png", &width, &height, 0, SOIL_LOAD_RGB);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    // Specular map
    image = SOIL_load_image("Content/Textures/container2_specular.png", &width, &height, 0, SOIL_LOAD_RGB);
    glBindTexture(GL_TEXTURE_2D, specularMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Set texture units
    lightingShader.Use();
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"),  0);
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check and call events
		glfwPollEvents();
		do_movement();

		// ** Rendering commands here **
#pragma region Rendering commands

		// Calculate DeltaTime
		//GLfloat deltaTime = (GLfloat)glfwGetTime() - startTime;
		//startTime = static_cast<GLfloat>(glfwGetTime());

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Activate shader
		lightingShader.Use();
		GLint lightColorLoc = glGetUniformLocation(lightingShader.Program, "lightColor");
		GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "lightPos");
		glUniform3f(lightColorLoc, 1.0f, 0.5f, 1.0f);
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z); // vertex shader calculates view position

		// Bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		// Bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		// Get/Set material uniform properties
		GLfloat shine = 64.0f;
		GLint matSpecularLoc = glGetUniformLocation(lightingShader.Program, "material.specular");
		GLint matShineLoc = glGetUniformLocation(lightingShader.Program, "material.shininess");
		glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
		glUniform1f(matShineLoc, shine);

		// Get/Set Lighting properties
		GLint lightAmbientLoc = glGetUniformLocation(lightingShader.Program, "light.ambient");
		GLint lightDiffuseLoc = glGetUniformLocation(lightingShader.Program, "light.diffuse");
		GLint lightSpecularLoc = glGetUniformLocation(lightingShader.Program, "light.specular");
		glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
		glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f);
		glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);

		// Camera/View transformation
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Projection
		glm::mat4 projection;
		projection = glm::perspective<GLfloat>(camera.Zoom, static_cast<GLfloat>(WIDTH) / static_cast<GLfloat>(HEIGHT), 0.1f, 100.0f);

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw
		glBindVertexArray(containerVAO);
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0); // Unbind VAO

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Note: to make something rotate around it's center, use the cos in one axis and the sin in the other to contrarrest the motion and rotate
		// make sure to add some value to move the object a bit far from it's center
		// Change the light's position values over time (can be done anywhere in the game loop actually, but try to do it at least before using the light source positions)
		/*lightPos.x = 2.0f * cos(glfwGetTime());
		lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
		lightPos.z = 2.0f * sin(glfwGetTime());*/

		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

#pragma endregion

		// Swap the buffers
		glfwSwapBuffers(window);
	}

	// De-allocate all resources
	glDeleteVertexArrays(1, &containerVAO);
	glDeleteBuffers(1, &VBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}

void LightingMaps::do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void LightingMaps::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		keys[key] = true;
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}
}

void LightingMaps::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<GLfloat>(yoffset));
}

void LightingMaps::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) // this bool variable is initially set to true
	{
		lastX = static_cast<GLfloat>(xpos);
		lastY = static_cast<GLfloat>(ypos);
		firstMouse = false;
	}

	GLfloat xoffset = static_cast<GLfloat>(xpos - lastX);
	// Screen coordinates go from top to bottom, but OpenGL has a bottom to top screen position
	GLfloat yoffset = static_cast<GLfloat>(lastY - ypos); // Reversed since y-coordinates range from bottom to top
	lastX = static_cast<GLfloat>(xpos);
	lastY = static_cast<GLfloat>(ypos);

	GLfloat sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

#pragma region Callback setup (with access to member variables)
void LightingMaps::SetCallbackFunctions(GLFWwindow* window)
{
	GLFWCallbackWrapper::SetApplication(this);
	glfwSetCursorPosCallback(window, GLFWCallbackWrapper::MousePositionCallback);
	glfwSetKeyCallback(window, GLFWCallbackWrapper::KeyboardCallback);
	glfwSetScrollCallback(window, GLFWCallbackWrapper::ScrollCallback);
}

LightingMaps* LightingMaps::GLFWCallbackWrapper::s_application = nullptr;

void LightingMaps::GLFWCallbackWrapper::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	s_application->MousePositionCallback(window, xpos, ypos);
}

void LightingMaps::GLFWCallbackWrapper::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	s_application->KeyboardCallback(window, key, scancode, action, mods);
}

void LightingMaps::GLFWCallbackWrapper::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	s_application->ScrollCallback(window, xoffset, yoffset);
}

void LightingMaps::GLFWCallbackWrapper::SetApplication(LightingMaps *application)
{
	GLFWCallbackWrapper::s_application = application;
}
#pragma endregion
