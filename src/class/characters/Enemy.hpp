#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Character.cc"

using namespace std;


class Enemy: public Character
{
    private:
        sf::Texture enemyTexture;
        sf::Sprite enemySprite;
        int knockBack = 250;
        float xPosition = 0;
        float yPosition = 0;
        float originalXPosition = 0;
        int animationIndex = 0;
        int healthPoints;

        sf::Clock animationClock;
        sf::Time animationCooldown;

    public:
        // 1 : Fighter, 2 : Warrior, 3 : Ranger
        int type;

        /*
        * Constructor for the Enemy class
        * @param x : x position of the enemy
        * @param y : y position of the enemy
        * @param type : type of the enemy
        * @return void
        */
        Enemy(float x, float y, int type);

        /*
        * Get the sprite of the enemy
        * @param void
        * @return sf::Sprite
        */
        sf::Sprite getEnemySprite();

        /*
        * Draw the enemy on the screen
        * @param window : the window to draw the enemy on
        * @param player : the player object
        * @return void
        */
        void drawEnemy(sf::RenderWindow &window, Player* player);

        /*
        * Reset the enemy to its original position
        * @param void
        * @return void
        */
        void resetEnemy();

        /*
        * Set the position of the enemy
        * @param x : x position of the enemy
        * @param y : y position of the enemy
        * @return void
        */
        void setPosition(float x, float y);

        /*
        * Get the position of the enemy
        * @param void
        * @return array<float, 2>
        */
        array<float, 2> getPosition();

        /*
        * Get the global bounds of the enemy
        * @param void
        * @return sf::FloatRect
        */
        int getKnockBack();

        /*
        * Attack the player
        * @param player : the player object
        * @return void
        */
        void attack(Player* player);

        /*
        * Get the damage of the enemy
        * @param void
        * @return int
        */
        int getDamage();

        /*
        * Get the health points of the enemy
        * @param void
        * @return int
        */
        int getHealthPoints();

        /*
        * Get the original x position of the enemy
        * @param void
        * @return float
        */
        float getOriginalXPosition();

        /*
        * Set the original x position of the enemy
        * @param x : the x position of the enemy
        * @return void
        */
        void setOriginalXPosition(float x);    
};