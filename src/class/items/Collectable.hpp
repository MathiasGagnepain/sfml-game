#pragma once

#include <string>
#include <iostream>
#include <array>

using namespace std;


class Collectable : public Item
{
    private:
        sf::Texture collectable1Texture, collectable2Texture, collectable3Texture, collectable4Texture;
        sf::Sprite collectable;
        float xPosition, yPosition;

    public:
        int score;
        bool isEat = false;
        bool isResetter;
        int type;

        /*
        * Constructor
        * @param type : the type of the collectable
        * @param x : x position of the collectable
        * @param y : y position of the collectable
        */
        Collectable(int type, float x, float y);

        /*
        * Collect the coin
        * @param player : the player object
        * @return void
        */
        void collectCoin(Player* player);

        /*
        * Draw the collectable on the screen
        * @param window : the window to draw the collectable on
        * @param player : the player object
        * @return void
        */
        void drawCollectable(sf::RenderWindow &window, Player* player);

        /*
        * Collide with the player
        * @param player : the player object
        * @return void
        */
        void collideWithPlayer(Player* player);

        /*
        * Reset the collectable to its original position
        * @param void
        * @return void
        */
        void resetCollectable();

        /*
        * Set the position of the collectable
        * @param x : x position of the collectable
        * @param y : y position of the collectable
        * @return void
        */
        void setPosition(float x, float y);

        /*
        * Get the position of the collectable
        * @param void
        * @return array<float, 2>
        */
        array<float, 2> getPosition();
};