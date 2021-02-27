#include "character.h"

#include <GL/glew.h>
#include "../external/stb/stb_image.h"
#include <GLFW/glfw3.h>
#include <iostream>


Character::Character(float centerX, float centerY, int width, int height, const Shader & shader)
    :   mShader(shader),
        mCenterX(centerX), mCenterY(centerY),
        mWidth(width), mHeight(height),
        mWalkState(0),
        mTimePerWalkSprite(0.1f), mDeltaTimeWalkSprite(0.0f),
        mGoRight(true)
{
}

void Character::SetSprite(int layers, const std::string texPaths[]) {
    mMaxWalkState = layers;
    for (int i = 0; i < layers; ++i) {
        Rectangle rect(mCenterX, mCenterY, mWidth, mHeight, mShader);
        rect.SetTexture(texPaths[i]);
        mWalkRects.push_back(rect);
    }
}


void Character::Update(float deltaTime, const bool keys[]) {
    mDeltaTimeWalkSprite += deltaTime;

    if (mDeltaTimeWalkSprite > mTimePerWalkSprite) {
        mDeltaTimeWalkSprite = 0.0f;
        if (keys[GLFW_KEY_A])
        {
            mGoRight = false;
            --mWalkState;
            if (mWalkState < 0) {
                mWalkState = mMaxWalkState -1;
            }
            mWalkState %= mMaxWalkState;

        }
        if (keys[GLFW_KEY_D])
        {
            mGoRight = true;
            ++mWalkState;
            mWalkState %= mMaxWalkState;
        }
    }
}


void Character::Draw() {
    mShader.SetUniform1i("goRight", mGoRight);
    mWalkRects.at(mWalkState).Draw();
}