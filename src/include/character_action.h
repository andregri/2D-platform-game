#ifndef CHARACTER_ACTION_H
#define CHARACTER_ACTION_H

#include <vector>
#include "rectangle.h"
#include "shader.h"

enum class Action_t {IDLE, WALK, RUN, JUMP};

class CharacterAction {
    public:
        CharacterAction();
        CharacterAction(Action_t type, bool unstoppable, float timePerSprite);
        void SetSprites(int numSprites, const std::string * spritePaths, float centerX, float centerY, int width, int height, const Shader & shader);
        void Update(float deltaTime, float centerX, float centerY);
        void Draw();
        int GetState();
        bool isActive();
        Action_t getType();
        bool isUnstoppable();

    private:
        Action_t m_type;
        float mCenterX, mCenterY;
        int mState, mNumStates;
        float mTimePerState, mDeltaTimeState;
        bool m_isUnstoppable;
        std::vector<Rectangle> mRects;
};

#endif