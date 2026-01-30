//
// Created by Adam on 30/01/2026.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(float fov, float aspectRatio, float nearClip, float farClip);
    Camera() : Camera(45.0f, 4.0f/3.0f, 0.1f, 100.0f) {}
    // Call every frame if camera moves
    void setPosition(const glm::vec3& position);
    void setRotation(float yaw, float pitch);

    const glm::mat4& getViewMatrix() const { return m_View; }
    const glm::mat4& getProjectionMatrix() const { return m_Projection; }
    glm::mat4 getViewProjectionMatrix() const { return m_Projection * m_View; }

    void SetAspectRatio(float aspect)
    {
        m_Aspect = aspect;
        RecalculateProjection();
    }

private:
    void RecalcViewMatrix();

    void RecalculateProjection()
    {
        m_Projection = glm::perspective(
            glm::radians(m_FOV),
            m_Aspect,
            m_Near,
            m_Far
        );
    }

    glm::vec3 position;
    float yaw;   // degrees
    float pitch; // degrees

    glm::mat4 m_View{};
    glm::mat4 m_Projection{};

    float m_FOV;
    float m_Aspect;
    float m_Near;
    float m_Far;
};
