#ifndef APP_HPP
#define APP_HPP

#include "app_delegate.hpp"

namespace learn_opengl {

class App {
   public:
    App(char const *title_, AppDelegate *delegate_);

    ~App();

    void run();

   private:
    char const *title_;
    AppDelegate *delegate_;
    void *window_;

    void createWindow();
};
}

#endif
