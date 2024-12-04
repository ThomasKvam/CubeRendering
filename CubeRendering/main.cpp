#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <Shader.cpp>

using namespace std;

int main() {
	GLFWwindow* window;
	//Initilizing the GLFW library
	if (!glfwInit()) {
		cout << "Failed to initilize GLFW" << endl;
		return -1;
	}

	//Creating a windowed mode and it's OpenGL context
	window = glfwCreateWindow(800, 800, "Cube Render", NULL, NULL);
	if (!window) {
		cout << "Failed to create window" << endl;
		return -1;
	}
	//Make windowed's context current
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		cout << "Could not initilize GLEW!" << endl;
	}
	cout << glGetString(GL_VERSION) << endl;

	//Points for the figure
	float vertices[] = {
		// Front face
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		// Back face
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		// Left face
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		// Right face
		 0.5f,  0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,

		 // Top face
		 -0.5f,  0.5f,  0.5f,
		  0.5f,  0.5f,  0.5f,
		  0.5f,  0.5f, -0.5f,
		  0.5f,  0.5f, -0.5f,
		 -0.5f,  0.5f, -0.5f,
		 -0.5f,  0.5f,  0.5f,

		 // Bottom face
		 -0.5f, -0.5f,  0.5f,
		 -0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f,  0.5f,
		 -0.5f, -0.5f,  0.5f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	ShaderProgramSource source = ParseShader("Resources/shaders/Basic.shader");

	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

	//Loop untill the window closes
	while (!glfwWindowShouldClose(window)) {
		//Setting window background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Drawing Cube with 36 different points
		glDrawArrays(GL_TRIANGLES, 0, 36);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}