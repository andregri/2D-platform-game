#include "scrolling_background.h"

#include <GLFW/glfw3.h>
#include "game_constants.h"

ScrollingBackground::ScrollingBackground(int winWidth, int winHeight, float groundHeight, const std::string & texPath, const Shader & shader, b2World & world)
    :   mShader(shader),
        mWinWidth(winWidth), mWinHeight(winHeight),
        mRect1(winWidth / 2, winHeight / 2, winWidth, winHeight, mShader),
        mRect2(winWidth + winWidth / 2 - 1, winHeight / 2, winWidth, winHeight, mShader)
{
    mRect1.SetTexture(texPath);
    mRect2.SetTexture(texPath);

    // Define the ground body.
	b2BodyDef groundBodyDef;
    groundBodyDef.position.Set((mWinWidth / PPM)*0.05f, 0.0f);

    // Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
	b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
	groundBox.SetAsBox((mWinWidth / PPM)*0.5f, (groundHeight / PPM)*0.5f);

    // Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);
}

void ScrollingBackground::Update(float deltaTime, const bool keys[]) {
    float velocity;
    if (keys[GLFW_KEY_LEFT_SHIFT]) { //Run
        velocity = 250 * deltaTime;
    }
    else {
        velocity = 150 * deltaTime;
    }

    // Scroll infinite background
    if (keys[GLFW_KEY_A])
    {
        mRect1.mCenterX += velocity;
        mRect2.mCenterX += velocity;
    }
    else if (keys[GLFW_KEY_D])
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