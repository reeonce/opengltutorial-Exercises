cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(learn_opengl)

#Bring the headers, such as Student.h into the project
# include_directories(include)

#Can manually add the sources using the set command as follows:
set(SOURCES src/hello_triangle/main.cpp src/hello_triangle/hello_triangle.cpp src/common/shader.cpp src/common/app.cpp)


#However, the file(GLOB...) allows for wildcard additions:
# file(GLOB SOURCES "*.cpp")

add_executable(hello_triangle ${SOURCES})

find_package(OpenGL REQUIRED)
target_link_libraries(hello_triangle ${OPENGL_LIBRARIES})
target_link_libraries(hello_triangle glfw3)
target_link_libraries(hello_triangle glew)
target_compile_features(hello_triangle PRIVATE cxx_range_for)
