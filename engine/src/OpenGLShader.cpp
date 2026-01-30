//
// Created by Adam on 30/01/2026.
//
#include <filesystem>
#include "Render/OpenGLShader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

// -----------------------------
// Constructor
// -----------------------------
OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath) {


    std::string vertexSrc = readFile(vertexPath);
    std::string fragmentSrc = readFile(fragmentPath);

    uint32_t vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
    uint32_t fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    // Link error checking
    int success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        char info[1024];
        glGetProgramInfoLog(programID, 1024, nullptr, info);
        std::cerr << "[OpenGLShader] Shader linking error:\n" << info << std::endl;
    }

    // Delete intermediate shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// -----------------------------
// Destructor
// -----------------------------
OpenGLShader::~OpenGLShader() {
    glDeleteProgram(programID);
}

// -----------------------------
// Bind / Unbind
// -----------------------------
void OpenGLShader::bind() { glUseProgram(programID); }
void OpenGLShader::unbind() { glUseProgram(0); }

// -----------------------------
// Set Uniforms
// -----------------------------
void OpenGLShader::setInt(const std::string& name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void OpenGLShader::setFloat(const std::string& name, float value) {
    glUniform1f(getUniformLocation(name), value);
}

void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

// -----------------------------
// Helpers
// -----------------------------
std::string OpenGLShader::readFile(const std::string& path) {
    const std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "[OpenGLShader] Failed to open file: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

uint32_t OpenGLShader::compileShader(const uint32_t type, const std::string& source) {
    const uint32_t shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Compile error checking
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, info);
        std::cerr << "[OpenGLShader] Shader compilation error ("
                  << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                  << "):\n" << info << std::endl;
    }

    return shader;
}

int OpenGLShader::getUniformLocation(const std::string& name) {
    if (uniformCache.contains(name))
        return uniformCache[name];

    const int location = glGetUniformLocation(programID, name.c_str());
    if (location == -1)
        std::cerr << "[OpenGLShader] Warning: uniform '" << name << "' does not exist!\n";

    uniformCache[name] = location;
    return location;
}

