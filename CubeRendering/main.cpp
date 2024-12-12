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
        glm::mat4 proj = glm::ortho(-400.0f, 400.0f, -400.0f, 400.0f, -400.0f, 400.0f);

        //If you want to move the cube:
        // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        //Binding the shader and pgn to the Cube
        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        Texture texture("res/textures/blue.png");

        //Adding a background color to the cube
        shader.SetUniform4f("u_BackgroundColor", 1.0f, 1.0f, 1.0f, 0.9f);

        //Adding the png to the cube
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        shader.Unbind();

        vb.Unbind();
        ib.Unbind();

        //Initilizing the renderer class
        Renderer renderer;

        float rotationX = 0.0f;
        float rotationY = 0.0f;

        //Timing variable
        double lastTime = glfwGetTime();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            //calculate elapsed time
            double currTime = glfwGetTime();
            double deltaTime = currTime - lastTime;
            lastTime = currTime;

            //Update rotation angles
            const GLfloat rotationSpeed = 40.0f; //degrees per second
            rotationX += rotationSpeed * deltaTime;
            rotationY += rotationSpeed * deltaTime;


            //Rotate around the X and Y axis at origo
            glm::mat4 modelX = glm::rotate(glm::mat4(1.0f), glm::radians(rotationX), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 modelY = glm::rotate(glm::mat4(1.0f), glm::radians(rotationY), glm::vec3(1.0f, 0.0f, 1.0f));

            //Add the roation to the projection and view
            glm::mat4 mvp = proj * modelX * modelY;

            //Binding shaders continously because the cube position changes
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);

            /* Render here */
            renderer.Clear();

            //Drawing the cube 
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
