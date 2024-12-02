#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void DrawCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength );

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;



int main() {
	//Inittialize GLFW
	glfwInit();

	//window specs / create window object
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cube Render", NULL, NULL);


	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	int screenWidth;
	int screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (!window) {
		std::cout << "Faild to create Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//introduce window into the current context
	glfwMakeContextCurrent(window);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000);
	glMatrixMode(GL_MODELVIEW);

	GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
	GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;

	//Timing variable
	double lastTime = glfwGetTime();

	//run window
	while (!glfwWindowShouldClose(window)) {
		//calculate elapsed time
		double currTime = glfwGetTime();
		double deltaTime = currTime - lastTime;
		lastTime = currTime;

		//Update rotation angles
		const GLfloat rotationSpeed = 80.0f; //degrees per second
		rotationX += rotationSpeed * deltaTime;
		rotationY += rotationSpeed * deltaTime * 2;


		//Change color of the window
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Render OpenGL here:
		glPushMatrix();
		glTranslatef(halfScreenWidth, halfScreenHeight, -500);
		glRotatef(rotationX, 1, 0, 0);
		glRotatef(rotationY, 0, 1, 0);
		glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);

		DrawCube(halfScreenWidth, halfScreenHeight,-500, 100);


		glPopMatrix();
		//Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and proccess events
		// Detects different proccesses and events
		glfwPollEvents();
	}

	//terminate window on exit
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}


void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength) {
	GLfloat halfSideLength = edgeLength * 0.5;

	GLfloat verticies[] =
	{
		//front face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, //top left
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, //top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, //bottom right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, //bottom left

		//back face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, //top left
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, //top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, //bottom right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, //bottom left

		//left face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, //top left
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, //top right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, //bottom right
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, //bottom left

		//right face
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, //top left
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, //top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, //bottom right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, //bottom left

		//top face
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, //top left
		centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, //top right
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, //bottom right
		centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, //bottom left

		//bottom face
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, //top left
		centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, //top right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, //bottom right
		centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, //bottom left
	};

	//Creating Color array for each side of the cube
	GLfloat colors[] = {
		// Front face (red)
		1.0f, 0.0f, 0.0f, // Top left
		1.0f, 0.0f, 0.0f, // Top right
		1.0f, 0.0f, 0.0f, // Bottom right
		1.0f, 0.0f, 0.0f, // Bottom left

		// Back face (green)
		0.0f, 1.0f, 0.0f, // Top left
		0.0f, 1.0f, 0.0f, // Top right
		0.0f, 1.0f, 0.0f, // Bottom right
		0.0f, 1.0f, 0.0f, // Bottom left

		// Left face (blue)
		0.0f, 0.0f, 1.0f, // Top left
		0.0f, 0.0f, 1.0f, // Top right
		0.0f, 0.0f, 1.0f, // Bottom right
		0.0f, 0.0f, 1.0f, // Bottom left

		// Right face (yellow)
		1.0f, 1.0f, 0.0f, // Top left
		1.0f, 1.0f, 0.0f, // Top right
		1.0f, 1.0f, 0.0f, // Bottom right
		1.0f, 1.0f, 0.0f, // Bottom left

		// Top face (cyan)
		0.0f, 1.0f, 1.0f, // Top left
		0.0f, 1.0f, 1.0f, // Top right
		0.0f, 1.0f, 1.0f, // Bottom right
		0.0f, 1.0f, 1.0f, // Bottom left

		// Bottom face (magenta)
		1.0f, 0.0f, 1.0f, // Top left
		1.0f, 0.0f, 1.0f, // Top right
		1.0f, 0.0f, 1.0f, // Bottom right
		1.0f, 0.0f, 1.0f, // Bottom left
	};

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Render squares
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// (xyz=3, datatype, stride/gap?, array) 
	glVertexPointer(3, GL_FLOAT, 0, verticies);
	glColorPointer(3, GL_FLOAT, 0, colors);

	//(Type of shape, startingpoint, numer of points)
	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
};
