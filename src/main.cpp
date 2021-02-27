#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../external/stb/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "shader.h"
#include "rectangle.h"
#include "scrolling_background.h"
#include "character.h"

bool Keys[1024] = {false};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int main(void)
{
    constexpr float WINDOW_WIDTH = 800;
    constexpr float WINDOW_HEIGHT = 450;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glfwSetKeyCallback(window, key_callback);


    /* Create a shader */
    Shader shader           = Shader("../common/vertex.shader", "../common/fragment.shader");
    Shader characterShader  = Shader("../common/vertex.shader", "../common/character_fragment.shader");

    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -1.0f, 1.0f);
    shader.Use();
    shader.SetUniformMatrix4f("view", view);
    shader.SetUniformMatrix4f("projection", projection);
    characterShader.Use();
    characterShader.SetUniformMatrix4f("view", view);
    characterShader.SetUniformMatrix4f("projection", projection);

    // Create a scrolling background
    ScrollingBackground scrollingBackground(WINDOW_WIDTH, WINDOW_HEIGHT, "../resources/background.png", shader);

    // Create a character
    // -------------------
    Character character(WINDOW_WIDTH / 2, 98.0f, 680 / 4, 472 / 4, characterShader);
    std::string walkSpritePaths[10] = {
        "../resources/dinosprite/Walk (1).png",
        "../resources/dinosprite/Walk (2).png",
        "../resources/dinosprite/Walk (3).png",
        "../resources/dinosprite/Walk (4).png",
        "../resources/dinosprite/Walk (5).png",
        "../resources/dinosprite/Walk (6).png",
        "../resources/dinosprite/Walk (7).png",
        "../resources/dinosprite/Walk (8).png",
        "../resources/dinosprite/Walk (9).png",
        "../resources/dinosprite/Walk (10).png"};
    character.SetSprite(10, walkSpritePaths);

    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /* Poll for and process events */
        glfwPollEvents();

        // UPDATE
        // -----------------
        scrollingBackground.Update(deltaTime, Keys);
        character.Update(deltaTime, Keys);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);        

        scrollingBackground.Draw();
        character.Draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Keys[key] = true;
        else if (action == GLFW_RELEASE)
            Keys[key] = false;
    }
}