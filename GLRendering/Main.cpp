// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other includes
#include <iostream>

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

#pragma region Shaders

/* Creating a very basic Vertex Shader using GLSL (OpenGL Shading Language)
* The current vertex shader is probably the most simple vertex shader we can imagine 
* because we did no processing whatsoever on the input data and simply forwarded it to the shader's output
*/
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

#pragma endregion Shaders

// The MAIN function, from here we start the application and run the game loop
int main()
{
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
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);

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

#pragma region VertexShader

	// Build and compile our shader program
	// Vertex shader
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

#pragma endregion FragmentShader

#pragma region Triangle

	// Because we want to render a single triangle we want to specify a total of three vertices with each vertex having a 3D position. 
	// We define them in normalized device coordinates (the visible region of OpenGL) in a GLfloat array
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);

	// The buffer type of a vertex buffer object is GL_ARRAY_BUFFER. OpenGL allows us to bind to several buffers at once as long as they have a different buffer type
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// We created the vertices, we made a buffer object to store those vertices (using the array buffer type)
	// now let's store those vertices on the VBO (Vertex Buffer Object)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

#pragma endregion Triangle

	// Init the game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwPollEvents();

		// Rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the buffers
		glfwSwapBuffers(window);
	}

	// Clean/delete all resources that were allocated
	glfwTerminate();
	
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, 
	// closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}