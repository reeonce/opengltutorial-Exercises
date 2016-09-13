#include "hello_triangle.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../common/shader.hpp"

namespace learn_opengl {

HelloTriangle::HelloTriangle() {
}

void HelloTriangle::onWindowInited(GLFWwindow *window) {
    // Create and compile our GLSL program from the shaders
    programID0 = LoadShaders("res/SimpleVertexShader.txt",
                             "res/GreenFragmentShader.txt");
    programID1 = LoadShaders("res/SimpleVertexShader.txt",
                             "res/YellowFragmentShader.txt");

    const GLfloat g_vertex_buffer_data[] = {
        0.5f, 0.5f, 0.0f,  // 右上角
        0.5f, 0.0f, 0.0f,  // 右下角
        0.0f, 0.0f, 0.0f,  // 左下角
        -0.5f, 0.5f, 0.0f, // 左上角
        -0.5f, 0.0f, 0.0f  // 左上角
    };

    GLuint indices[] = {
        0, 1, 2, // 第一个三角形
        2, 3, 4  // 第二个三角形
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 4. 解绑VAO（不是EBO！）
    glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void HelloTriangle::onFrameUpdate() {
    // Dark blue background
    glClearColor(0.3f, 0.4f, 0.5f, 1.0f);
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);

    glUseProgram(programID0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(programID1);
    glDrawArrays(GL_TRIANGLES, 2, 3);

    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0);

    glDisableVertexAttribArray(0);
}

void HelloTriangle::onTerminate() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    printf("onTerminate\n");
}
}
