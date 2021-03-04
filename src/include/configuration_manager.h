#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

class ConfigurationManager {
    public:
        static ConfigurationManager& instance() {
            static ConfigurationManager* instance = new ConfigurationManager();
            return *instance;
        } 

        // Getters
        float getWindowWidth();
        float getWindowHeight();

        // Setters
        void setWindowWidth(float w);
        void setWindowHeight(float h);

    private:
        ConfigurationManager() {};
        ~ConfigurationManager();
        float m_winWidth;
        float m_winHeight;
};

#endif