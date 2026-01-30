#include "Core.h"
#include "Engine/Engine.h"
#include "Render/OpenGLShader.h"
#include "Engine/Camera.h"
#include <glm/glm.hpp>
#include "Platform/Config.h"

int main() {
    Config winConfig;
    winConfig.width = 1920;
    winConfig.height = 1080;
    winConfig.title = "Moose Sandbox";

    Engine engine(winConfig);

    const float aspectRatio = static_cast<float>(winConfig.width) / static_cast<float>(winConfig.height);
    std::shared_ptr<OpenGLShader> shader;
    Camera camera(45.0f, aspectRatio, 0.1f, 100.0f);
    GLuint VAO, VBO;

    engine.SetInitFunction([&]() {
        constexpr float vertices[] = {
             0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
        glEnableVertexAttribArray(0);

        shader = std::make_shared<OpenGLShader>(
            "Assets/Shaders/basic.vert",
            "Assets/Shaders/basic.frag"
        );

        camera.setPosition({0.0f, 0.0f, 3.0f});
    });

    engine.SetRenderFunction([&] {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->bind();
        glm::mat4 mvp = camera.getViewProjectionMatrix();
        shader->setMat4("u_MVP", mvp);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    });

    engine.Run();
}
