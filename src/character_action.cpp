#include "character_action.h"
#include <iostream>

CharacterAction::CharacterAction(Action_t type, bool unstoppable,float timePerSprite)
    : m_type(type),
    m_isUnstoppable(unstoppable),
    mTimePerState(timePerSprite),
    mState(0)
{
    std::cout << "CharacterAction::CharacterAction(Action_t type, bool unstoppable,float timePerSprite)\n";
}


CharacterAction::CharacterAction()
{
    std::cout << "CharacterAction::CharacterAction()\n";
}


void CharacterAction::SetSprites(int num, const std::string * paths,
    float centerX, float centerY, int width, int height, const Shader & shader)
{
    std::cout << "void CharacterAction::SetSprites(int num, const std::string * paths,"
        "float centerX, float centerY, int width, int height, const Shader & shader)\n";
    
    mCenterX = centerX;
    mCenterY = centerY;
    mNumStates = num;

    for (int i = 0; i < mNumStates; ++i) {
        Rectangle rect(centerX, centerY, width, height, shader);
        rect.SetTexture(paths[i]);
        mRects.push_back(rect);
    }
}


void CharacterAction::Update(float deltaTime, float centerX, float centerY)
{
    //std::cout << "void CharacterAction::Update(float deltaTime, const bool keys[])\n";
    
    if (mState == 0) {
        ++mState;
    }
    else {
        mDeltaTimeState += deltaTime;

        if (mDeltaTimeState > mTimePerState) {
            mDeltaTimeState = 0.0f;
            ++mState;
            mState %= mNumStates;
        }
    }

    mCenterX = centerX;
    mCenterY = centerY;
}


void CharacterAction::Draw()
{
    mRects.at(mState).mCenterX = mCenterX;
    mRects.at(mState).mCenterY = mCenterY;
    mRects.at(mState).Draw();
}

int CharacterAction::GetState()
{
    return mState;
}

bool CharacterAction::isActive() 
{
    return mState > 0;
}

Action_t CharacterAction::getType()
{
    return m_type;
}

bool CharacterAction::isUnstoppable()
{
    return m_isUnstoppable;
}