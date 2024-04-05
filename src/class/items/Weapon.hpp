#pragma once

#include <string>
#include <iostream>

using namespace std;

class Weapon: public Item
{
    private:
        sf::Texture weaponTexture;
        sf::Sprite weaponSprite;

        int id;
        int damage;
        bool isDefense;
        float xPosition, yPosition;

    public:
        /*
        * Constructor
        * @param id : the id of the weapon
        * @param damage : the damage of the weapon
        * @param isDefense : the type of the weapon
        * @param x : x position of the weapon
        * @param y : y position of the weapon
        * @return void
        */
        Weapon(int id, int damage, bool isDefense, float x, float y);

        /*
        * Draw weapon
        * @param window : the window to draw the weapon on
        * @param player : the player object
        * @return void
        */
        void drawWeapon(sf::RenderWindow &window, Player* player);

        /*
        * Collide with the player
        * @param player : the player object
        * @return void
        */
        void playerCollide(Player* player);

        /*
        * Reset weapon
        * @param void
        * @return void
        */
        void resetWeapon();
};