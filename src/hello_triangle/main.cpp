#include "hello_triangle.hpp"
#include "../common/app.hpp"

using namespace learn_opengl;

int main(int argc, char *argv[]) {
    char const *title = "Hello triangle";
    AppDelegate *appDelegate = new HelloTriangle();
    App *app = new App(title, appDelegate);
    app->run();
    delete app;
    return 0;
}
