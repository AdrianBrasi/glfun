cmake_minimum_required(VERSION 3.10)
project(glfun)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set policy CMP0072 to use GLVND
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

if(APPLE)
    find_package(SDL2 REQUIRED)
    if(NOT GLEW_FOUND)
        set(GLEW_INCLUDE_DIRS "/opt/homebrew/opt/glew/include")
        set(GLEW_LIBRARIES "/opt/homebrew/opt/glew/lib/libGLEW.dylib")
    endif()
else()
    find_package(SDL2 REQUIRED)
    find_package(GLEW REQUIRED)
endif()

include_directories(${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})

link_directories(${GLFW_LIBRARY_DIRS} ${GLEW_LIBRARY_DIRS} ${SDL2_LIBRARY_DIRS})

add_executable(glfun src/main.cpp)

if(APPLE)
    target_link_libraries(glfun
            ${GLFW_LIBRARIES}
            ${GLEW_LIBRARIES}
            ${SDL2_LIBRARIES}
            ${OPENGL_gl_LIBRARY}
            "-framework Cocoa"
            "-framework OpenGL"
            "-framework IOKit")
else()
    target_link_libraries(glfun
            ${GLFW_LIBRARIES}
            ${GLEW_LIBRARIES}
            ${SDL2_LIBRARIES}
            ${OPENGL_gl_LIBRARY}
            ${OPENGL_opengl_LIBRARY}
            ${OPENGL_glx_LIBRARY}
            pthread
            X11
            Xxf86vm
            Xrandr
            Xi
            Xcursor)
endif()
