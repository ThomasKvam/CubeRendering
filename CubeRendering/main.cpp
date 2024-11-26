#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


int main() {
	//Inittialize GLFW
	glfwInit();


	//window specs / create window object
	GLFWwindow* window = glfwCreateWindow(800, 800, "YouTube Tutorial", NULL, NULL);
	if (window == NULL) {
		std::cout << "Faild to create Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//introduce window into the current context
	glfwMakeContextCurrent(window);
	glViewport(0, 0, 800, 800);



	//triangle endpoints
	float verticies[] = {
		//x   y    z
		-0.5f, 0.5f, 0.0f, //top left corner
		0.5f, 0.5f, 0.0f, //top right corner
		0.5f, -0.5f, 0.0f, //bottom right corner
		-0.5f, -0.5f, 0.0f // bottom left corner
	};


	//run window
	while (!glfwWindowShouldClose(window)) {

		//Change color of the window
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Render square
		glEnableClientState(GL_VERTEX_ARRAY);

		// (xyz=3, datatype, stride/gap?, array) 
		glVertexPointer(3, GL_FLOAT, 0, verticies);

		//(Type of shape, startingpoint, numer of points)
		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);

		//Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and proccess events
		glfwPollEvents();
	}

	//terminate window on exit
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}