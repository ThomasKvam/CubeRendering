#include "Camera.h"

Camera::Camera(glm::vec3 position) : m_Position(position), m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_Up(glm::vec3(0.0f, 1.0f, 0.0f)), m_Speed(1000.0f), m_Sensitivity(100.0f) {

}

glm::mat4 Camera::GetViewMatrix() const {
	return glm::lookAt(m_Position, m_Position * m_Front, m_Up);
}

void Camera::ProcessKeyboardInput(int direction, float deltaTime)
{
    float velocity = m_Speed * deltaTime;
    if (direction == GLFW_KEY_W) m_Position -= m_Front * velocity;
    if (direction == GLFW_KEY_S) m_Position += m_Front * velocity;
    if (direction == GLFW_KEY_A) m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * velocity;
    if (direction == GLFW_KEY_D) m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * velocity;
    if (direction == GLFW_KEY_SPACE) m_Position += m_Up * velocity;
    if (direction == GLFW_KEY_BACKSPACE) m_Position -= m_Up * velocity;
}
