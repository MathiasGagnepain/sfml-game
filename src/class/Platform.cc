#include <string>
#include <iostream>

class Platform 
{
    private:
        // Platform
        sf::Texture platformTexture;
        sf::Sprite platform;

    public:
    
        Platform(string path, float posX, float posY, float scaleX, float scaleY){
            this->platformTexture.loadFromFile(path);
            this->platform.setTexture(platformTexture);
            this->platform.setScale(scaleX, scaleY);
            this->platform.setPosition(posX, posY);
        }

        sf::FloatRect getGlobalBounds(){
            return this->platform.getGlobalBounds();
        }

        sf::Sprite getPlatform(){
            return this->platform;
        }
        // platformTexture.loadFromFile("../src/assets/platform.png");
        // platform.setTexture(platformTexture);
        // platform.setScale(1.0f, .75f);
        // platform.setPosition(700.0f, 480.0f);
};