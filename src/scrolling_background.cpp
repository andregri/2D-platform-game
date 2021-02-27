#include "scrolling_background.h"

#include <GLFW/glfw3.h>

ScrollingBackground::ScrollingBackground(int winWidth, int winHeight, const std::string & texPath, const Shader & shader)
    :   mShader(shader),
        mWinWidth(winWidth), mWinHeight(winHeight),
        mRect1(winWidth / 2, winHeight / 2, winWidth, winHeight, mShader),
        mRect2(winWidth + winWidth / 2 - 1, winHeight / 2, winWidth, winHeight, mShader)
{
    mRect1.SetTexture(texPath);
    mRect2.SetTexture(texPath);
}

void ScrollingBackground::Update(float deltaTime, const bool keys[]) {
    float velocity = 150 * deltaTime;
    // Scroll infinite background
    if (keys[GLFW_KEY_A])
    {
        mRect1.mCenterX += velocity;
        mRect2.mCenterX += velocity;
    }
    if (keys[GLFW_KEY_D])
    {
        mRect1.mCenterX -= velocity;
        mRect2.mCenterX -= velocity;
    }

    if (mRect1.mCenterX < -mWinWidth / 2) {
        mRect1.mCenterX = mWinWidth + mWinWidth / 2 - 5;
    }
    if (mRect2.mCenterX < -mWinWidth / 2) {
        mRect2.mCenterX = mWinWidth + mWinWidth / 2 - 5;
    }
    if (mRect1.mCenterX > mWinWidth + mWinWidth / 2) {
        mRect1.mCenterX = -mWinWidth / 2 + 5;
    }
    if (mRect2.mCenterX > mWinWidth + mWinWidth / 2) {
        mRect2.mCenterX = -mWinWidth / 2 + 5;
    }
}

void ScrollingBackground::Draw() {
    mRect1.Draw();
    mRect2.Draw();
}