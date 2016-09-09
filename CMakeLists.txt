cmake_minimum_required(VERSION 3.3)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(simplewindow)

#Bring the headers, such as Student.h into the project
# include_directories(include)

#Can manually add the sources using the set command as follows:
set(SOURCES src/simplewindow.cpp common/shader.cpp)


#However, the file(GLOB...) allows for wildcard additions:
# file(GLOB SOURCES "*.cpp")

add_executable(simplewindow ${SOURCES})

find_package(OpenGL REQUIRED)
target_link_libraries(simplewindow ${OPENGL_LIBRARIES})
target_link_libraries(simplewindow glfw3)
target_link_libraries(simplewindow glew)
