cmake_minimum_required(VERSION 3.10)
project(glfun)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(SDL2 REQUIRED)

if(NOT GLEW_FOUND)
    set(GLEW_INCLUDE_DIRS "/opt/homebrew/opt/glew/include")
    set(GLEW_LIBRARIES "/opt/homebrew/opt/glew/lib/libGLEW.dylib")
endif()

include_directories(${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})

link_directories(${GLFW_LIBRARY_DIRS} ${GLEW_LIBRARY_DIRS} ${SDL2_LIBRARY_DIRS})

add_executable(glfun src/main.cpp)

target_link_libraries(glfun
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${SDL2_LIBRARIES}
        ${OPENGL_gl_LIBRARY}
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework IOKit")

