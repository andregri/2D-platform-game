#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
    public:
        Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
        ~Shader();
        void Use();

        void SetUniform1i(std::string name, int value);

    private:
        unsigned int mShader;

        unsigned int Compile(std::string sourcePath, unsigned int vertexType);
};

#endif