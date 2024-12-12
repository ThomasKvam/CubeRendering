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
    window = glfwCreateWindow(800, 800, "Cube Rendering", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "ERROR!" << std::endl;
    {
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

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        VertexArray va;
        VertexBuffer vb(positions, 8 * 5 * sizeof(float));
        
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 36);

        //Projection
        glm::mat4 proj = glm::ortho(-400.0f, 400.0f, -400.0f, 400.0f, -400.0f, 400.0f);

        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 mvp = proj * view; // *model;

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();

        Texture texture("res/textures/blue.png");

        //Adding a background color to the square
        shader.SetUniform4f("u_BackgroundColor", 1.0f, 1.0f, 1.0f, 0.9f);

        shader.SetUniformMat4f("u_MVP", mvp);

        //Adding the png to the square
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        shader.Unbind();

        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        float rotationX = 0.0f;
        float rotationY = 0.0f;


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            /* Calculate rotation */
            rotationX += 0.05f; // Adjust speed here
            if (rotationX > 100.0f) // Optional: Reset after a full rotation
                rotationX -= 0.01f;
            else if (rotationX < 100.0f) rotationX += 0.01f;


            rotationY += 0.05f; // Adjust speed here
            if (rotationY > 100.0f) // Optional: Reset after a full rotation
                rotationY -= 0.01f;
            else if (rotationY < 100.0f) rotationY += 0.01f;

            glm::mat4 modelX = glm::rotate(glm::mat4(0.05f), glm::radians(rotationX), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 modelY = glm::rotate(glm::mat4(0.05f), glm::radians(rotationY), glm::vec3(1.0f, 0.0f, 0.0f));
            glm::mat4 mvp = proj * view * modelX * modelY;

            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);


            /* Render here */
            renderer.Clear();

            renderer.Draw(va, ib, shader);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
