#include "app.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

namespace learn_opengl {

#define WINDOW_WIDTH 200
#define WINDOW_HEIGHT 200

App::App(char const *title_, AppDelegate *delegate_) {
    this->title_ = title_;
    this->delegate_ = delegate_;
}

void App::run() {
    createWindow();

    GLFWwindow *window = (GLFWwindow *)window_;
    delegate_->onWindowInited(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        delegate_->onFrameUpdate();

        // Swap buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    delegate_->onTerminate();
}

void key_callback(GLFWwindow *indow, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(indow, GL_TRUE);
    }
}

void App::createWindow() {
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

    window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title_, nullptr,
                               nullptr);
    if (window_ == nullptr) {
        fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    GLFWwindow *window = (GLFWwindow *)window_;

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

App::~App() {
}
}
