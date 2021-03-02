#ifndef SCROLLING_BACKGROUND_H
#define SCROLLING_BACKGROUND_H

#include "rectangle.h"
#include "shader.h"
#include <box2d/box2d.h>

class ScrollingBackground {
    public:
        ScrollingBackground(int winWidth, int winHeight, float groundHeight, const std::string & texPath, const Shader & shader, b2World & world);
        ~ScrollingBackground() {};
        void Update(float deltaTime, const bool keys[]);
        void Draw();

    private:
        Shader mShader;
        Rectangle mRect1, mRect2;
        float mWinWidth, mWinHeight;
        b2Body* mGroundBody;
};

#endif