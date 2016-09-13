#ifndef APP_DELEGATE_HPP
#define APP_DELEGATE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace learn_opengl {

class AppDelegate {
   public:
    virtual void onWindowInited(GLFWwindow *window) = 0;

    virtual void onFrameUpdate() = 0;

    virtual void onTerminate() = 0;
};
}

#endif
