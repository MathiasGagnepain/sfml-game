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
        /*
        * Constructor
        * @param path: string
        * @param posX: float
        * @param posY: float
        * @param scaleX: float
        * @param scaleY: float
        * @return void
        */
        Platform(string path, float posX, float posY, float scaleX, float scaleY);

        /*
        * Get the global bounds of the platform
        * @param void
        * @return sf::FloatRect
        */
        sf::FloatRect getGlobalBounds();

        /*
        * Get the sprite of the platform
        * @param void
        * @return sf::Sprite
        */
        sf::Sprite getPlatform();

        /*
        * Get the position of the platform
        * @param void
        * @return array<float, 2>
        */
        array<float, 2> getPosition();

        /*
        * Set the position of the platform
        * @param x : x position of the platform
        * @param y : y position of the platform
        * @return void
        */
        void setPosition(float x, float y);
};