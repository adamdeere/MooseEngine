#pragma once
#include "Shader.h"

class OpenGLShader : public Shader {
public:
    OpenGLShader(const std::string& vertexPath,
                 const std::string& fragmentPath
    );

    ~OpenGLShader();

    void bind() override;
    void unbind() override;

    void setInt(const std::string& name, int value) override;
    void setFloat(const std::string& name, float value) override;
    void setMat4(const std::string& name, const glm::mat4& value) override;

private:
    uint32_t programID;
    std::unordered_map<std::string, int> uniformCache;

    static std::string readFile(const std::string& path);
    int getUniformLocation(const std::string& name);

    // Helpers

    static uint32_t compileShader(uint32_t type, const std::string& source);
};
