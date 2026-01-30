//
// Created by Adam on 30/01/2026.
//

#include "Core.h"
#include "Engine/Camera.h"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(const float fov, const float aspectRatio, const float nearClip, const float farClip)
    : position(0.0f, 0.0f, 3.0f), yaw(-90.0f), pitch(0.0f), fov(fov),
      aspect(aspectRatio), nearClip(nearClip), farClip(farClip)
{
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
    recalcViewMatrix();
}

void Camera::setPosition(const glm::vec3& pos) {
    position = pos;
    recalcViewMatrix();
}

void Camera::setRotation(float newYaw, float newPitch) {
    yaw = newYaw;
    pitch = glm::clamp(newPitch, -89.0f, 89.0f); // prevent gimbal lock
    recalcViewMatrix();
}

void Camera::recalcViewMatrix() {
    // Compute front vector using only stable functions
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    viewMatrix = glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
}

