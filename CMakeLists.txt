cmake_minimum_required(VERSION 3.10)
project(Tutorial VERSION 1.0)

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW3
add_subdirectory(external/glfw-3.3.2)
include_directories(external/glfw-3.3.2/include)

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_PATH})

# STB_IMAGE
add_library(STB_IMAGE "external/stb/stb_image.cpp")


# add the executable
add_executable(Tutorial
    src/main.cpp
    src/shader.cpp
    src/rectangle.cpp
    src/scrolling_background.cpp
    src/character.cpp
    src/character_action.cpp
)

target_include_directories(Tutorial
    PRIVATE src/include    
)

target_link_libraries(Tutorial PUBLIC 
    ${OPENGL_LIBRARY}
    ${GLEW_LIBRARY}
    glfw
    ${GLFW_LIBRARIES}
    STB_IMAGE
)