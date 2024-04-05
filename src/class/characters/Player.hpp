#pragma once

#include <string>
#include <iostream>
#include "Character.cc"

using namespace std;

class Player: public Character
{
    private:
        int jumpHeight = 250;
        int score = 0;
        int maxHealth = 100;

        /*
        * This function checks if the player has reached the end of the level
        * @param sf::Sprite levelEnd
        * @return bool
        */
        bool checkEnd(sf::Sprite levelEnd);
   
        /*
        * This function handles the player's gravity
        * @param sf::Sprite ground
        * @param Platform* platform
        * @return void
        */
        void gravity(sf::Sprite ground, Platform* platform);

        /*
        * This function makes the player jump
        * @param void
        * @return void
        */
        void jumping();

    public:
        // TODO: set this in private
        int inventory[2] = {0, 0};
        float xPosition = 20;
        float yPosition = 0;
        float xVelocity = 0;
        float yVelocity = 0;
        bool isJumping = false;
        bool isCrouching = false;
        bool isMiddleScreen = false;
        float originalPlayerPosition = 0;
        int selectedSlot = 0;
        int animationIndex = 0;
        int healthPoints = 100;
        float baseDamage = 2;
        bool levelEnded = false;

        sf::Clock jumpClock, animationClock;
        sf::Time jumpCooldown, animationCooldown;
        sf::Texture healthBarTexture, playerTexture;
        sf::Sprite healthBar, healthBarBackground, playerSprite;

        /*
        * This is the constuctor for the Player class
        * @param string name
        * @return void
        */
        Player(string name);

        /*
        * This function resets the player's position
        * @param void
        * @return void
        */
        void resetPosition();

        /*
        * This function moves the player to the right
        * @param void
        * @return void
        */
        void moveRight();

        /*
        * This function moves the player to the left
        * @param void
        * @return void
        */
        void moveLeft();

        /*
        * This function makes the player jump
        * @param void
        * @return void
        */
        void jump();

        /*
        * This function makes the player crouch
        * @param sf::Sprite ground
        * @return void
        */
        void crouch(sf::Sprite ground);

        /*
        * This function handles the physics of the player
        * @param sf::Sprite ground
        * @param Platform* platform
        * @param sf::Sprite levelEnd
        * @return void
        */
        void physics(sf::Sprite ground, Platform* platform, sf::Sprite levelEnd);

        /*
        * This function gets the jump cooldown
        * @param void
        * @return sf::Time
        */
        sf::Time getJumpCooldown();

        /*
        * This function gets the player's score
        * @param void
        * @return int
        */
        int getScore();

        /*
        * This function sets the player's score
        * @param int score
        * @return void
        */
        void setScore(int score);

        /*
        * This function draws the health bar
        * @param sf::RenderWindow &window
        * @return void
        */
        void drawHealthBar(sf::RenderWindow &window);

        /*
        * This function gets the global bounds of the player
        * @param void
        * @return sf::FloatRect
        */
        sf::FloatRect getGlobalBounds();

        /*
        * This function draws the player
        * @param sf::RenderWindow &window
        * @return void
        */
        void drawPlayer(sf::RenderWindow &window);

        /*
        * This function gets the selected slot
        * @param void
        * @return int
        */
        int getSelectedSlot();

        /*
        * This function selects the slot
        * @param void
        * @return void
        */
        void selectSlot();
};