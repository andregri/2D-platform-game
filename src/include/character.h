#ifndef CHARACTER_H
#define CHARACTER_H

#include "shader.h"
#include "rectangle.h"
#include "character_action.h"
#include <vector>
#include <map>
#include <box2d/box2d.h>

class Character {
    public:
        float mCenterX, mCenterY;
        Character(float centerX, float centerY, int width, int height, const Shader & shader, b2World & world);
        void AddAction(const std::string & name, CharacterAction & action, int numSprites, const std::string * spritePaths);
        void Update(float deltaTime, const bool keys[]);
        void Draw();

    private:
        int mWidth, mHeight;
        Shader mShader;
        bool mGoRight;
        std::string mAction;
        std::map<std::string, CharacterAction> mActions;
        b2Body* mBody;
        bool mIsJumping;
};

#endif