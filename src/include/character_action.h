#ifndef CHARACTER_ACTION_H
#define CHARACTER_ACTION_H

#include <vector>
#include "rectangle.h"
#include "shader.h"

class CharacterAction {
    public:
        CharacterAction();
        CharacterAction(float timePerSprite);
        void SetSprites(int numSprites, const std::string * spritePaths, float centerX, float centerY, int width, int height, const Shader & shader);
        void Update(float deltaTime, float centerX, float centerY);
        void Draw();

    private:
        float mCenterX, mCenterY;
        int mState, mNumStates;
        float mTimePerState, mDeltaTimeState;
        std::vector<Rectangle> mRects;
};

#endif