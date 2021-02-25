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

    glCullFace(GL_FRONT_AND_BACK);

    /* Create a shader */
    Shader shader = Shader("../common/vertex.shader", "../common/fragment.shader");


    /* Draw a rectangle */
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    /* Load the texture */
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../resources/bricks.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    shader.Use();
    shader.SetUniform1i("ourTexture", 0);

    glm::mat4 model         = glm::mat4(1.0f);
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -1.0f, 1.0f);
    shader.SetUniformMatrix4f("view", view);
    shader.SetUniformMatrix4f("model", model);
    shader.SetUniformMatrix4f("projection", projection);
    
    /* Test rectangle class */
    Rectangle background1(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);
    Rectangle background2(WINDOW_WIDTH + WINDOW_WIDTH / 2 - 1, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);
    background1.SetTexture("../resources/background.png", shader);
    background2.SetTexture("../resources/background.png", shader);

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

        /* Process input */
        float velocity = 300 * deltaTime;
        // Scroll infinite background
        int state_a = glfwGetKey(window, GLFW_KEY_A);
        if (state_a == GLFW_PRESS)
        {
            background1.mCenterX += velocity;
            background2.mCenterX += velocity;
        }
        int state_d = glfwGetKey(window, GLFW_KEY_D);
        if (state_d == GLFW_PRESS)
        {
            background1.mCenterX -= velocity;
            background2.mCenterX -= velocity;
        }

        if (background1.mCenterX < -WINDOW_WIDTH / 2) {
            background1.mCenterX = WINDOW_WIDTH + WINDOW_WIDTH / 2 - 5;
        }
        if (background2.mCenterX < -WINDOW_WIDTH / 2) {
            background2.mCenterX = WINDOW_WIDTH + WINDOW_WIDTH / 2 - 5;
        }
        if (background1.mCenterX > WINDOW_WIDTH + WINDOW_WIDTH / 2) {
            background1.mCenterX = -WINDOW_WIDTH / 2 + 5;
        }
        if (background2.mCenterX > WINDOW_WIDTH + WINDOW_WIDTH / 2) {
            background2.mCenterX = -WINDOW_WIDTH / 2 + 5;
        }

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);        

        background1.Draw(shader);
        background2.Draw(shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}