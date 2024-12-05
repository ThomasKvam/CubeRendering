#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GenerateCube.h" // Include the header file


// Function to initialize the cube vertex data and buffer
unsigned int createCubeVertices() {
    // Cube vertex data (positions)
    float vertices[] = {
        // positive x face
        0.5f,0.5f,0.5f,
        0.5f,0.5f,-0.5f,
        0.5f,-0.5f,0.5f,
        0.5f,-0.5f,-0.5f,
        // negative x face
        -0.5f,0.5f,0.5f,
        -0.5f,0.5f,-0.5f,
        -0.5f,-0.5f,0.5f,
        -0.5f,-0.5f,-0.5f

    };



    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);



    return buffer; // Return the buffer to bind later if necessary
}

unsigned int createCubeIndices() {
    unsigned int indices[] = {
        1, 0, 3,
        1, 3, 5,
        1, 5, 0,

        2, 3, 0,
        2, 0, 6,
        2, 3, 6,

        4, 5, 0,
        4, 0, 6,
        4, 5, 6,

        7, 5, 6,
        7, 3, 6,
        7, 5, 3

    };

    unsigned int indiceBuffer;
    glGenBuffers(1, &indiceBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * 3 * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);

    return indiceBuffer;
}

