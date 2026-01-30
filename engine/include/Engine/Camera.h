//
// Created by Adam on 30/01/2026.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(float fov, float aspectRatio, float nearClip, float farClip);

    // Call every frame if camera moves
    void setPosition(const glm::vec3& position);
    void setRotation(float yaw, float pitch);

    const glm::mat4& getViewMatrix() const { return viewMatrix; }
    const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
    glm::mat4 getViewProjectionMatrix() const { return projectionMatrix * viewMatrix; }

private:
    void recalcViewMatrix();

    glm::vec3 position;
    float yaw;   // degrees
    float pitch; // degrees

    glm::mat4 viewMatrix{};
    glm::mat4 projectionMatrix{};

    float fov;
    float aspect;
    float nearClip;
    float farClip;
};
