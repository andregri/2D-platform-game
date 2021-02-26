#ifndef SCROLLING_BACKGROUND_H
#define SCROLLING_BACKGROUND_H

#include "rectangle.h"
#include "shader.h"

class ScrollingBackground {
    public:
        ScrollingBackground(int winWidth, int winHeight, const std::string & texPath, const Shader & shader);
        ~ScrollingBackground() {};
        void Update(float deltaTime, const bool keys[]);
        void Draw();

    private:
        Shader mShader;
        Rectangle mRect1, mRect2;
        float mWinWidth, mWinHeight; 
};

#endif