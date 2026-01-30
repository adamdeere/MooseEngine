//
// Created by Adam on 30/01/2026.
//

#include "Core.h"
#include "Engine/Camera.h"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(const float fov, const float aspectRatio, const float nearClip, const float farClip)
    : position(0.0f, 0.0f, 3.0f), yaw(-90.0f), pitch(0.0f), m_FOV(fov),
      m_Aspect(aspectRatio), m_Near(nearClip), m_Far(farClip)
{
    m_Projection = glm::perspective(glm::radians(fov), m_Aspect, nearClip, farClip);
    RecalcViewMatrix();
}

void Camera::setPosition(const glm::vec3& pos) {
    position = pos;
    RecalcViewMatrix();
}

void Camera::setRotation(float newYaw, float newPitch) {
    yaw = newYaw;
    pitch = glm::clamp(newPitch, -89.0f, 89.0f); // prevent gimbal lock
    RecalcViewMatrix();
}

void Camera::RecalcViewMatrix() {
    // Compute front vector using only stable functions
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    m_View = glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
}

