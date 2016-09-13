#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include "shader.hpp"

namespace learn_opengl {
static std::string readShaderFile(const char *file) {
    std::string code;
    std::ifstream shaderStream(file, std::ios::in);
    if (shaderStream.is_open()) {
        std::string Line = "";
        while (getline(shaderStream, Line))
            code += "\n" + Line;
        shaderStream.close();
    } else {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", file);
        getchar();
        return 0;
    }
    return code;
}

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path) {
    Shader *vertexShader = new Shader(vertex_file_path, GL_VERTEX_SHADER);
    Shader *fragmentShader = new Shader(fragment_file_path, GL_FRAGMENT_SHADER);

    // Link the program
    printf("Linking program\n");
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShader->shaderId);
    glAttachShader(programId, fragmentShader->shaderId);

    glLinkProgram(programId);

    GLint result = GL_FALSE;
    int infoLogLength;

    // Check the program
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programId, infoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(programId, vertexShader->shaderId);
    glDetachShader(programId, fragmentShader->shaderId);

    delete vertexShader;
    delete fragmentShader;

    return programId;
}

Shader::Shader(const char *filePath, GLenum shaderType) {
    this->shaderType_ = shaderType;

    shaderId = glCreateShader(shaderType);
    std::string code = readShaderFile(filePath);

    GLint result = GL_FALSE;
    int infoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", filePath);
    char const *sourcePointer = code.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, nullptr);
    glCompileShader(shaderId);

    // Check Vertex Shader
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> shaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(shaderId, infoLogLength, NULL, &shaderErrorMessage[0]);
        printf("%s\n", &shaderErrorMessage[0]);
    }
}

Shader::~Shader() {
    glDeleteShader(shaderId);
}
}
