#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    virtual ~Shader() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual void setInt(const std::string& name, int value) = 0;
    virtual void setFloat(const std::string& name, float value) = 0;
    virtual void setMat4(const std::string& name, const glm::mat4& value) = 0;
};
