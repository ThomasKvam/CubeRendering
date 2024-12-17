#pragma once

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

class Camera
{
private:
    glm::vec3 m_Position;   // Camera position
    glm::vec3 m_Front;      // Camera forward direction
    glm::vec3 m_Up;         // Camera up direction
    float m_Speed;          // Movement speed
    float m_Sensitivity;    // Mouse sensitivity

public:
    Camera(glm::vec3 position);

    glm::mat4 GetViewMatrix() const;
    void ProcessKeyboardInput(int direction, float deltaTime);
    glm::vec3 GetPosition() const { return m_Position; }
};