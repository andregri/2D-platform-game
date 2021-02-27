#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include "shader.h"

class Rectangle {
    public:
        float mCenterX, mCenterY;
        Rectangle(float centerX, float centerY, int width, int height, const Shader & shader);
        void SetTexture(const std::string & path);
        void Draw();

    private:
        unsigned int VAO, VBO, EBO;
        float vertices[32] = {
            // positions          // colors           // texture coords
             1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
             1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
        };
        unsigned int indices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        Shader mShader;
        int mWidth, mHeight;
        unsigned int mTexture;

};

#endif