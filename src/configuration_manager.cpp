#include "configuration_manager.h"

float ConfigurationManager::getWindowWidth()
{
    return m_winWidth;
}

float ConfigurationManager::getWindowHeight()
{
    return m_winHeight;
}

void ConfigurationManager::setWindowWidth(float w)
{
    if (w > 0) {
        m_winWidth = w;
    }
    else {
        throw "Window width cannot be null or negative";
    }
}

void ConfigurationManager::setWindowHeight(float h)
{
    if (h > 0) {
        m_winHeight = h;
    }
    else {
        throw "Window height cannot be null or negative";
    }
}
