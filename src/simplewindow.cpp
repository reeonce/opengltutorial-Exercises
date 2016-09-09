// cc -o simplewindow simplewindow.cpp -framework GLUT -framework OpenGL -lglfw3
// -lglew

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include "../common/shader.hpp"

#define WINDOW_TITLE_PREFIX "Magical GL"

int CurrentWidth = 200, CurrentHeight = 120, WindowHandle = 0;

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
    -0.5f, -0.50f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.8f, 0.0f,
};

void Initialize(int, char *[]);
void InitWindow(int, char *[], GLFWwindow **);
void ResizeFunction(int, int);
void RenderFunction(void);
void mainloop(GLFWwindow *window);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

int main(int argc, char *argv[]) {
    Initialize(argc, argv);

    return 0;
}

void Initialize(int argc, char *argv[]) {
    GLFWwindow *window = nullptr;
    InitWindow(argc, argv, &window);

    fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

    if (!window) {
        fprintf(stderr, "ERROR: Failed to init window.\n");
        return;
    }

    mainloop(window);
}

void InitWindow(int argc, char *argv[], GLFWwindow **pwindow) {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                   GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    GLFWwindow *window = glfwCreateWindow(CurrentWidth, CurrentHeight,
                                          WINDOW_TITLE_PREFIX, nullptr, nullptr);
    if (window == nullptr) {
        fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    *pwindow = window;

    glfwMakeContextCurrent(window); // Initialize GLEW

    glewExperimental = GL_TRUE; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetKeyCallback(window, key_callback);
}

void mainloop(GLFWwindow *window) {
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data, GL_STATIC_DRAW);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders("res/SimpleVertexShader.txt",
                                   "res/SimpleFragmentShader.txt");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

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

        // Swap buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
}

void key_callback(GLFWwindow *indow, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(indow, GL_TRUE);
    }
}
