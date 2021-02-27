#ifndef CHARACTER_H
#define CHARACTER_H

#include "shader.h"
#include "rectangle.h"
#include <vector>

class Character {
    public:
        float mCenterX, mCenterY;
        int mWalkState, mMaxWalkState;
        float mTimePerWalkSprite;
        Character(float centerX, float centerY, int width, int height, const Shader & shader);
        void SetSprite(int layers, const std::string texPaths[]);
        void Update(float deltaTime, const bool keys[]);
        void Draw();

    private:
        int mWidth, mHeight;
        Shader mShader;
        unsigned int mTextureArray;
        std::vector<Rectangle> mWalkRects;
        float mDeltaTimeWalkSprite;
        bool mGoRight;
};

#endif