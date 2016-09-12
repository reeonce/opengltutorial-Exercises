#include "hello_triangle.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../common/shader.hpp"

static const GLfloat g_vertex_buffer_data[] = {
    -0.5f, -0.50f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.8f, 0.0f,
};

namespace learn_opengl {

HelloTriangle::HelloTriangle() {
}

void HelloTriangle::onWindowInited(GLFWwindow *window) {
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &this->vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data, GL_STATIC_DRAW);

    // Create and compile our GLSL program from the shaders
    this->programID = LoadShaders("res/SimpleVertexShader.txt",
                                  "res/SimpleFragmentShader.txt");
}

void HelloTriangle::onFrameUpdate() {
    // Dark blue background
    glClearColor(0.3f, 0.4f, 0.5f, 0.0f);
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0,        // attribute 0. No particular reason for 0, but
                                    // must match the layout in the shader.
                          3,        // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                          );

    glUseProgram(programID);
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0,
                 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}
}
