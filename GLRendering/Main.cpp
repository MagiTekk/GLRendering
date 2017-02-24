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

const GLchar* fragmentShaderSource = "#version 330 core \n"
"out vect4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
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

#pragma region LinkShaders

	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

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

#pragma endregion

	// delete the shader objects once we've linked them into the program object; we no longer need them anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

#pragma region Triangle

	// Because we want to render a single triangle we want to specify a total of three vertices with each vertex having a 3D position. 
	// We define them in normalized device coordinates (the visible region of OpenGL) in a GLfloat array
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, // Left  
		0.5f, -0.5f, 0.0f, // Right 
		0.0f,  0.5f, 0.0f  // Top   
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	// The buffer type of a vertex buffer object is GL_ARRAY_BUFFER. OpenGL allows us to bind to several buffers at once as long as they have a different buffer type
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// We created the vertices, we made a buffer object to store those vertices (using the array buffer type)
	// now let's store those vertices on the VBO (Vertex Buffer Object)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Tell OpenGL how it should interpret the vertex data (per vertex attribute)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
	glBindVertexArray(0);

#pragma endregion Triangle

	// Init the game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwPollEvents();

		// Rendering commands here
		
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0); // Unbind VAO

		// Swap the buffers
		glfwSwapBuffers(window);
	}

	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

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