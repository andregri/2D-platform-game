#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include "shader.h"

class Rectangle {
    public:
        Rectangle(int centerX, int centerY, int width, int height);
        void SetTexture(const std::string & path, const Shader & shader);
        void Draw(const Shader & shader);

    private:
        unsigned int VAO, VBO, EBO;
        float vertices[32] = {
            // positions          // colors           // texture coords
             1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
             1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
        };
        const unsigned int indices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        int mCenterX, mCenterY, mWidth, mHeight;
        unsigned int mTexture;

};

#endif