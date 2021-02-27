#include "character.h"

#include <GL/glew.h>
#include "../external/stb/stb_image.h"
#include <GLFW/glfw3.h>
#include <iostream>


Character::Character(float centerX, float centerY, int width, int height, const Shader & shader)
    :   mShader(shader),
        mCenterX(centerX), mCenterY(centerY),
        mWidth(width), mHeight(height),
        mGoRight(true), mAction("idle")
{
}

void Character::AddAction(const std::string & name, CharacterAction & action, int numSprites, const std::string * spritePaths)
{
    std::cout << "void Character::AddAction\n";

    action.SetSprites(numSprites, spritePaths, mCenterX, mCenterY, mWidth, mHeight, mShader);
    mActions[name] = action;
}


void Character::Update(float deltaTime, const bool keys[])
{
    if (keys[GLFW_KEY_A]) {
        if (keys[GLFW_KEY_LEFT_SHIFT]) {
            mAction = "run";
            mActions["run"].Update(deltaTime);
        }
        else {
            mAction = "walk";
            mActions["walk"].Update(deltaTime);
        }
        mGoRight = false;
    }
    else if (keys[GLFW_KEY_D]) {
        if (keys[GLFW_KEY_LEFT_SHIFT]) {
            mAction = "run";
            mActions["run"].Update(deltaTime);
        }
        else {
            mAction = "walk";
            mActions["walk"].Update(deltaTime);
        }
        mGoRight = true;
    }
    else {
        mAction = "idle";
        mActions["idle"].Update(deltaTime);
    }
}


void Character::Draw()
{
    mShader.SetUniform1i("goRight", mGoRight);
    mActions[mAction].Draw();
}