#include <Shader.cpp>
#include <headers/GenerateCube.h> // Include the header file

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
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        cout << "Could not initialize GLEW!" << endl;
        return -1;
    }
    cout << glGetString(GL_VERSION) << endl;

    // Call create cube function
    createCubeVertices();
    createCubeIndices();

    // Load and compile shaders
    ShaderProgramSource source = ParseShader("Resources/shaders/Basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    GLCall(glUseProgram(shader));

    int location = glGetUniformLocation(shader, "u_Color");
    if (location < 0) {
        cout << "Could not get Uniform Location" << endl;
    }
   
    float r = 0.0f;
    float increment = 0.05f;

    // Loop until the window closes
    while (!glfwWindowShouldClose(window)) {
        // Set window background color
        GLCall(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // Drawing a Cube using triangles with 36 different points
        GLCall(glUniform4f(location, r, 1.0f, 1.0f, 1.0f));
        GLCall(glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f) {
            increment = -0.05f;
        }
        else if (r < 0) {
            increment = 0.05f;
        }

        r += increment;

        // Swap buffers
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    GLCall(glDeleteProgram(shader));
    glfwTerminate();
    return 0;
}
