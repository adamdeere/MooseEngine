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
        // Cube data: 36 vertices (6 faces * 2 triangles * 3 vertices)
        struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
    };

        // Cube vertices
        const Vertex cubeVertices[] = {
    // Front face (+Z)
    {{-0.5f, -0.5f, 0.5f}, {0,0,1}, {0,0}, {1,0,0}, {0,1,0}},
    {{0.5f, -0.5f, 0.5f}, {0,0,1}, {1,0}, {1,0,0}, {0,1,0}},
    {{0.5f, 0.5f, 0.5f}, {0,0,1}, {1,1}, {1,0,0}, {0,1,0}},
    {{0.5f, 0.5f, 0.5f}, {0,0,1}, {1,1}, {1,0,0}, {0,1,0}},
    {{-0.5f, 0.5f, 0.5f}, {0,0,1}, {0,1}, {1,0,0}, {0,1,0}},
    {{-0.5f, -0.5f, 0.5f}, {0,0,1}, {0,0}, {1,0,0}, {0,1,0}},

    // Back face (-Z)
    {{0.5f, -0.5f, -0.5f}, {0,0,-1}, {0,0}, {-1,0,0}, {0,1,0}},
    {{-0.5f, -0.5f, -0.5f}, {0,0,-1}, {1,0}, {-1,0,0}, {0,1,0}},
    {{-0.5f, 0.5f, -0.5f}, {0,0,-1}, {1,1}, {-1,0,0}, {0,1,0}},
    {{-0.5f, 0.5f, -0.5f}, {0,0,-1}, {1,1}, {-1,0,0}, {0,1,0}},
    {{0.5f, 0.5f, -0.5f}, {0,0,-1}, {0,1}, {-1,0,0}, {0,1,0}},
    {{0.5f, -0.5f, -0.5f}, {0,0,-1}, {0,0}, {-1,0,0}, {0,1,0}},

    // Left face (-X)
    {{-0.5f, -0.5f, -0.5f}, {-1,0,0}, {0,0}, {0,0,1}, {0,1,0}},
    {{-0.5f, -0.5f, 0.5f}, {-1,0,0}, {1,0}, {0,0,1}, {0,1,0}},
    {{-0.5f, 0.5f, 0.5f}, {-1,0,0}, {1,1}, {0,0,1}, {0,1,0}},
    {{-0.5f, 0.5f, 0.5f}, {-1,0,0}, {1,1}, {0,0,1}, {0,1,0}},
    {{-0.5f, 0.5f, -0.5f}, {-1,0,0}, {0,1}, {0,0,1}, {0,1,0}},
    {{-0.5f, -0.5f, -0.5f}, {-1,0,0}, {0,0}, {0,0,1}, {0,1,0}},

    // Right face (+X)
    {{0.5f, -0.5f, 0.5f}, {1,0,0}, {0,0}, {0,0,-1}, {0,1,0}},
    {{0.5f, -0.5f, -0.5f}, {1,0,0}, {1,0}, {0,0,-1}, {0,1,0}},
    {{0.5f, 0.5f, -0.5f}, {1,0,0}, {1,1}, {0,0,-1}, {0,1,0}},
    {{0.5f, 0.5f, -0.5f}, {1,0,0}, {1,1}, {0,0,-1}, {0,1,0}},
    {{0.5f, 0.5f, 0.5f}, {1,0,0}, {0,1}, {0,0,-1}, {0,1,0}},
    {{0.5f, -0.5f, 0.5f}, {1,0,0}, {0,0}, {0,0,-1}, {0,1,0}},

    // Top face (+Y)
    {{-0.5f, 0.5f, 0.5f}, {0,1,0}, {0,0}, {1,0,0}, {0,0,-1}},
    {{0.5f, 0.5f, 0.5f}, {0,1,0}, {1,0}, {1,0,0}, {0,0,-1}},
    {{0.5f, 0.5f, -0.5f}, {0,1,0}, {1,1}, {1,0,0}, {0,0,-1}},
    {{0.5f, 0.5f, -0.5f}, {0,1,0}, {1,1}, {1,0,0}, {0,0,-1}},
    {{-0.5f, 0.5f, -0.5f}, {0,1,0}, {0,1}, {1,0,0}, {0,0,-1}},
    {{-0.5f, 0.5f, 0.5f}, {0,1,0}, {0,0}, {1,0,0}, {0,0,-1}},

    // Bottom face (-Y)
    {{-0.5f, -0.5f, -0.5f}, {0,-1,0}, {0,0}, {1,0,0}, {0,0,1}},
    {{0.5f, -0.5f, -0.5f}, {0,-1,0}, {1,0}, {1,0,0}, {0,0,1}},
    {{0.5f, -0.5f, 0.5f}, {0,-1,0}, {1,1}, {1,0,0}, {0,0,1}},
    {{0.5f, -0.5f, 0.5f}, {0,-1,0}, {1,1}, {1,0,0}, {0,0,1}},
    {{-0.5f, -0.5f, 0.5f}, {0,-1,0}, {0,1}, {1,0,0}, {0,0,1}},
    {{-0.5f, -0.5f, -0.5f}, {0,-1,0}, {0,0}, {1,0,0}, {0,0,1}},
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

        // Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void *>(nullptr));

        // Normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Normal)));

        // TexCoords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, TexCoords)));

        // Tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Tangent)));

        // Bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Bitangent)));

        glBindVertexArray(0);


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
