#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.cpp>
#include "GenerateCube.h" // Include the header file

using namespace std;

int main() {
    GLFWwindow* window;
    // Initializing the GLFW library
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    // Creating a windowed mode and its OpenGL context
    window = glfwCreateWindow(800, 800, "Cube Render", NULL, NULL);
    if (!window) {
        cout << "Failed to create window" << endl;
        glfwTerminate();
        return -1;
    }

    // Make windowed context current
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        cout << "Could not initialize GLEW!" << endl;
        return -1;
    }
    cout << glGetString(GL_VERSION) << endl;

    // Call create cube function
    createCube();

    // Load and compile shaders
    ShaderProgramSource source = ParseShader("Resources/shaders/Basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    // Loop until the window closes
    while (!glfwWindowShouldClose(window)) {
        // Set window background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Drawing a Cube using triangles with 36 different points
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
