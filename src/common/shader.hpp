#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>

namespace learn_opengl {

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);

class Shader {
   public:
    GLuint shaderId;

    Shader(const char *filePath, GLenum shaderType);
    ~Shader();

   private:
    GLenum shaderType_;
};
}

#endif
