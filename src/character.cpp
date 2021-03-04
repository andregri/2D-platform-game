#include "character.h"

#include <GL/glew.h>
#include "../external/stb/stb_image.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "game_constants.h"


Character::Character(float centerX, float centerY, int width, int height, const Shader & shader, b2World & world)
    :   mShader(shader),
        mCenterX(centerX), mCenterY(centerY),
        mWidth(width), mHeight(height),
        mGoRight(true), m_currentAction(Action_t::IDLE), mIsJumping(false)
{
    std::cout << "Character::Character(float centerX, float centerY, int width, int height, const Shader & shader, b2World & world)\n";

    // Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(mCenterX / PPM, mCenterY / PPM);
	mBody = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(mWidth / PPM * 0.5f, mHeight / PPM * 0.5f);

    // Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

    // Add the shape to the body.
	mBody->CreateFixture(&fixtureDef);
}

void Character::AddAction(CharacterAction* action, int numSprites, const std::string * spritePaths)
{
    std::cout << "void Character::AddAction\n";

    action->SetSprites(numSprites, spritePaths, mCenterX, mCenterY, mWidth, mHeight, mShader);
    mActions[action->getType()] = action;
}


void Character::Update(float deltaTime, const bool keys[])
{
    b2Vec2 position = mBody->GetPosition();
    mCenterX = position.x * PPM;
    mCenterY = position.y * PPM;

    if (!mActions[m_currentAction]->isUnstoppable() || !mActions[m_currentAction]->isActive()) {
        if(keys[GLFW_KEY_SPACE]) {
            m_currentAction = Action_t::JUMP;
            b2Vec2 vel = mBody->GetLinearVelocity();
            vel.y = 8;  //upwards - don't change x velocity
            mBody->SetLinearVelocity(vel);
        }
        else if (keys[GLFW_KEY_A]) {
            if (keys[GLFW_KEY_LEFT_SHIFT]) {
                m_currentAction = Action_t::RUN;
            }
            else {
                m_currentAction = Action_t::WALK;
            }
            mGoRight = false;
        }
        else if (keys[GLFW_KEY_D]) {
            if (keys[GLFW_KEY_LEFT_SHIFT]) {
                m_currentAction = Action_t::RUN;
            }
            else {
                m_currentAction = Action_t::WALK;
            }
            mGoRight = true;
        }
        else {
            m_currentAction = Action_t::IDLE;
        }
    }

    mActions[m_currentAction]->Update(deltaTime, mCenterX, mCenterY);
}


void Character::Draw()
{
    mShader.SetUniform1i("goRight", mGoRight);
    mActions[m_currentAction]->Draw();
}