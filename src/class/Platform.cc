#include <string>
#include <iostream>
#include <array>

using namespace std;

class Platform 
{
    private:
        // Platform
        sf::Texture platformTexture;
        sf::Sprite platform;
        float posX, posY;

    public:
    
        Platform(string path, float posX, float posY, float scaleX, float scaleY){
            this->posX = posX;
            this->posY = posY;

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

        array<float, 2> getPosition(){
           array<float, 2> position;
            position = {this->posX, this->posY};
            return position;
        }

        void setPosition(float x, float y){
            this->posX = x;
            this->posY = y;

            this->platform.setPosition(this->posX, this->posY);
        }
};