#ifndef HELLO_TRIANGLE_HPP
#define HELLO_TRIANGLE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../common/app_delegate.hpp"

namespace learn_opengl {

class HelloTriangle : public AppDelegate {
   public:
    HelloTriangle();

    void onWindowInited(GLFWwindow *window);

    void onFrameUpdate();

    void onTerminate();

   private:
    GLuint programID0;
    GLuint programID1;
    GLuint EBO;
    GLuint VAO;
    GLuint VBO;
};
}

#endif
