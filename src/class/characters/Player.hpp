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

        /*
        * This function gets the player's position
        * @param void
        * @return array<float, 2>
        */
        array<float, 2> getPosition();

        /*
        * This function sets the player's position
        * @param float x
        * @param float y
        * @return void
        */
        void setPosition(float x, float y);

        /*
        * This function gets the player's inventory slot
        * @param int index
        * @return int
        */
        int getInventory(int index);

        /*
        * This function sets the player's inventory slot
        * @param int index
        * @param int value
        * @return void
        */
        void setInventory(int index, int value);

        /*
        * This function gets the player's velocity
        * @param void
        * @return array<float, 2>
        */
        array<float, 2> getVelocity();

        /*
        * This function gets the player's sprite
        * @param void
        * @return sf::Sprite
        */
        sf::Sprite getPlayerSprite();

        /*
        * This function set the level ended state
        * @param bool levelEnd
        * @return void
        */
        void setLevelEnd(bool levelEnd);

        /*
        * This function sets the player's health points
        * @param int healthPoints
        * @return void
        */
        void setHealthPoints(int healthPoints);

        /*
        * This function gets the player's health points
        * @param void
        * @return int
        */
        int getHealthPoints();

        /*
        * This function sets the player's jumping state
        * @param bool isJumping
        * @return void
        */
        void setIsJumping(bool isJumping);

        /*
        * This function gets the player's jumping state
        * @param void
        * @return bool
        */
        bool getIsJumping();

        /*
        * This function gets the level ended state
        * @param void
        * @return bool
        */
        bool getLevelEnd();

        /*
        * This function sets the player's velocity
        * @param float x
        * @param float y
        * @return void
        */
        void setVelocity(float x, float y);

        /*
        * This function gets the player's crouching state
        * @param void
        * @return bool
        */
        bool getIsCrouching();

        /*
        * This function sets the player's crouching state
        * @param bool isCrouching
        * @return void
        */
        void setIsCrouching(bool isCrouching);
};