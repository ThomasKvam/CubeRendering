#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 900, "Cube Rendering", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //Initilizing the GLEW library
    if (glewInit() != GLEW_OK)
        std::cout << "ERROR!" << std::endl;
    {
        //Defining the front and backface of the cube
        float positions[] = {
            -150.0f, -150.0f, -150.0f, 0.0f, 0.0f, //Bottom left
            150.0f, -150.0f, -150.0f, 1.0f, 0.0f, //Bottom right
            150.0f, 150.0f, -150.0f, 1.0f, 1.0f, //Top right
            -150.0f, 150.0f, -150.0f, 0.0f, 1.0f, //Top left

            -150.0f, -150.0f, 150.0f, 0.0f, 0.0f, //Bottom left
            150.0f, -150.0f, 150.0f, 1.0f, 0.0f, //Bottom right
            150.0f, 150.0f, 150.0f, 1.0f, 1.0f, //Top right
            -150.0f, 150.0f, 150.0f, 0.0f, 1.0f, //Top left

        };

        //Connecting lines between front- and backface points 
        unsigned int indices[] = {
            // Front face
            0, 1, 2,
            2, 3, 0,

            // Back face
            4, 5, 6,
            6, 7, 4,

            // Left face
            4, 0, 3,
            3, 7, 4,

            // Right face
            1, 5, 6,
            6, 2, 1,

            // Top face
            3, 2, 6,
            6, 7, 3,

            // Bottom face
            4, 5, 1,
            1, 0, 4
        };

        //Enabling blend texture rendering
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        //Initilizing the VertexArray class
        VertexArray va;
        VertexBuffer vb(positions, 8 * 5 * sizeof(float));
        
        //Initilizing the VertexBuffer class
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 36);

        //Projection defenition (-x, x, -y, y, -z, z)
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1000.0f / 900.0f, 0.1f, 10000.0f);

        //Creating a shader and texture class based on shader file and a png
        Shader shader("res/shaders/Basic.shader");
        Texture texture("res/textures/blue.png");

        //Binding the shader to the program
        shader.Bind();

        //Adding a background color and texture to the cube
        shader.SetUniform4f("u_BackgroundColor", 1.0f, 1.0f, 1.0f, 0.9f);
        shader.SetUniform1i("u_Texture", 0);

        //Binding the texture to the program
        texture.Bind();

        //Unbinding to clear up allocated space
        va.Unbind();
        shader.Unbind();

        vb.Unbind();
        ib.Unbind();

        //Initilizing the renderer class
        Renderer renderer;

        Camera camera(glm::vec3(0.0f, 0.0f, -800.0f));
        float lastFrame = 0.0f;

        /* Loop until the user closes the window */
        float angle = 0.0f; // Initial rotation angle

        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = (float)glfwGetTime();
            float deltaTime = currentFrame - lastFrame; // Time between frames
            lastFrame = currentFrame;

            // Update the rotation angle over time
            angle += deltaTime * 60.0f; // Speed of rotation (50 degrees/sec)

            // Process camera movement input
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera.ProcessKeyboardInput(GLFW_KEY_W, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera.ProcessKeyboardInput(GLFW_KEY_S, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera.ProcessKeyboardInput(GLFW_KEY_A, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera.ProcessKeyboardInput(GLFW_KEY_D, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
                camera.ProcessKeyboardInput(GLFW_KEY_SPACE, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
                camera.ProcessKeyboardInput(GLFW_KEY_BACKSPACE, deltaTime);

            // Clear screen
            renderer.Clear();

            // Create the model matrix for cube rotation
            glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 1.0f, 0.0f)); // Rotate around Y-axis and X-axis

            // Get the view matrix from the camera
            glm::mat4 view = camera.GetViewMatrix();

            // Final MVP matrix
            glm::mat4 mvp = proj * view * model;

            // Pass the MVP matrix to the shader
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);

            // Draw the cube
            renderer.Draw(va, ib, shader);

            // Swap buffers and poll events
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

    }

    glfwTerminate();
    return 0;
}
