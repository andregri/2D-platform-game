#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../external/stb/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <box2d/box2d.h>

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

    
    // Set physics with box2d
    // -------------------
    //const float PPM = 32.0f; // Pixel per Meter

    // Define the gravity vector.
    b2Vec2 gravity(0.0f, -10.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    b2World world(gravity);    

    // Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
    float frameRate = 60.0f;
	float timeStep = 1.0f / frameRate;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;


    // Create a scrolling background
    ScrollingBackground scrollingBackground(WINDOW_WIDTH, WINDOW_HEIGHT, 85.0f, "../resources/background.png", shader, world);

    // Create a character
    // -------------------
    Character character(WINDOW_WIDTH / 2, 200.0f, 680 / 4, 472 / 4, characterShader, world);

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
    CharacterAction walkAction(Action_t::WALK, false, 0.1f);
    character.AddAction(&walkAction, 10, walkSpritePaths);

    std::string runSpritePaths[8] = {
        "../resources/dinosprite/Run (1).png",
        "../resources/dinosprite/Run (2).png",
        "../resources/dinosprite/Run (3).png",
        "../resources/dinosprite/Run (4).png",
        "../resources/dinosprite/Run (5).png",
        "../resources/dinosprite/Run (6).png",
        "../resources/dinosprite/Run (7).png",
        "../resources/dinosprite/Run (8).png"};
    CharacterAction runAction(Action_t::RUN, false, 0.05f);
    character.AddAction(&runAction, 8, runSpritePaths);

    std::string idleSpritePaths[10] = {
        "../resources/dinosprite/Idle (1).png",
        "../resources/dinosprite/Idle (2).png",
        "../resources/dinosprite/Idle (3).png",
        "../resources/dinosprite/Idle (4).png",
        "../resources/dinosprite/Idle (5).png",
        "../resources/dinosprite/Idle (6).png",
        "../resources/dinosprite/Idle (7).png",
        "../resources/dinosprite/Idle (8).png",
        "../resources/dinosprite/Idle (9).png",
        "../resources/dinosprite/Idle (10).png"};
    CharacterAction idleAction(Action_t::IDLE, false, 0.1f);
    character.AddAction(&idleAction, 10, idleSpritePaths);

    std::string jumpSpritePaths[12] = {
        "../resources/dinosprite/Jump (1).png",
        "../resources/dinosprite/Jump (2).png",
        "../resources/dinosprite/Jump (3).png",
        "../resources/dinosprite/Jump (4).png",
        "../resources/dinosprite/Jump (5).png",
        "../resources/dinosprite/Jump (6).png",
        "../resources/dinosprite/Jump (7).png",
        "../resources/dinosprite/Jump (8).png",
        "../resources/dinosprite/Jump (9).png",
        "../resources/dinosprite/Jump (10).png",
        "../resources/dinosprite/Jump (11).png",
        "../resources/dinosprite/Jump (12).png"};
    CharacterAction jumpAction(Action_t::JUMP, true, 0.15f);
    character.AddAction(&jumpAction, 12, jumpSpritePaths);

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

        if (deltaTime >= timeStep) {
            lastFrame = currentFrame;

            /* Poll for and process events */
            glfwPollEvents();

            // Compute World physics
            world.Step(timeStep, velocityIterations, positionIterations);

            

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