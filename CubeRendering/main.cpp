#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
void DrawCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength );

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

int main() {
	//Inittialize GLFW
	glfwInit();

	//window specs / create window object
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cube Render", NULL, NULL);


	glfwSetKeyCallback(window, keyCallback);
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

	//run window
	while (!glfwWindowShouldClose(window)) {

		//Change color of the window
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Render OpenGL here:
		glPushMatrix();
		glTranslatef(halfScreenWidth, halfScreenHeight, -500);
		glRotatef(rotationX, 1, 0, 0);
		glRotatef(rotationY, 0, 1, 0);
		glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);

		DrawCube(halfScreenWidth, halfScreenHeight, -500, 200);

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
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Render squares
	glEnableClientState(GL_VERTEX_ARRAY);

	// (xyz=3, datatype, stride/gap?, array) 
	glVertexPointer(3, GL_FLOAT, 0, verticies);

	//(Type of shape, startingpoint, numer of points)
	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
};


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	const GLfloat rotationSpeed = 10;

	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
		case GLFW_KEY_UP:
			rotationX -= rotationSpeed;
			break;
		case GLFW_KEY_DOWN:
			rotationX += rotationSpeed;
			break;
		case GLFW_KEY_RIGHT:
			rotationY += rotationSpeed;
			break;
		case GLFW_KEY_LEFT:
			rotationY -= rotationSpeed;
			break;
		}

	}
};