#include <string>
#include <iostream>
#include "Player.hpp"

using namespace std;

class Player: public Character
{
    public:
        int inventory[2] = {0, 0};
        float xPosition = 20;
        float yPosition = 0;
        float xVelocity = 0;
        float yVelocity = 0;
        bool isJumping = false;
        bool isCrouching = false;
        bool isMiddleScreen = false;
        float originalPlayerPosition = 0;
        float offsetX = 0;
        int selectedSlot = 0;
        int animationIndex = 0;

        int healthPoints = 100;
        float baseDamage = 2;
        bool levelEnded = false;

        sf::Clock jumpClock, animationClock;
        sf::Time jumpCooldown, animationCooldown;

        sf::Texture healthBarTexture, playerTexture;
        sf::Sprite healthBar, healthBarBackground, playerSprite;

        Player(string name){
            this->name = name;

            
            this->healthBarTexture.loadFromFile(HEALTH_BAR);
            this->healthBar.setTexture(healthBarTexture);
            this->healthBarBackground.setTexture(healthBarTexture);

            // Player
            this->playerTexture.loadFromFile(PLAYER[0]);
            this->playerSprite.setTexture(playerTexture);
            this->playerSprite.setScale(sf::Vector2f(0.2f, 0.2f));
        }

        void resetPosition(){
            this->xPosition = 20;
            this->yPosition = 400;
            this->xVelocity = 0;
            this->yVelocity = 0;
            this->inventory[0] = 0;
            this->inventory[1] = 0;
        }

        void moveRight(){
            this->xVelocity = 5;
        }

        void moveLeft(){
            this->xVelocity = -5;
        }

        void jump(){
            this->isJumping = true;
            this->originalPlayerPosition = this->yPosition;
            this->yVelocity = -10;
        }

        void crouch(sf::Sprite ground){
            this->isJumping = false;

            float playerHeight = playerSprite.getTexture()->getSize().y * this->playerSprite.getScale().y;

            if (this->playerSprite.getPosition().y + playerHeight/4 < ground.getPosition().y - 20) {
                this->yPosition += 10;
            }

            this->isCrouching = true;
            this->xVelocity = 0;
        }

        void physics(sf::Sprite ground, Platform* platform, sf::Sprite levelEnd){
            if (this->xPosition <= 0 && this->xVelocity < 0){
                this->xPosition = 0;
                this->xVelocity = 0;
            }
            this->xPosition += this->xVelocity;
            jumping();
            gravity(ground, platform);
            this->levelEnded = checkEnd(levelEnd);
        }

        sf::Time getJumpCooldown(){
            return this->jumpClock.getElapsedTime(); 
        }

        int getScore(){
            return this->score;
        }

        void setScore(int score){
            this->score = score;
        }

        void drawHealthBar(sf::RenderWindow &window){
            this->healthBarBackground.setScale(0.5f, 0.5f);
            this->healthBarBackground.setPosition(600, 10);
            this->healthBarBackground.setColor(sf::Color(128, 128, 128, 128));
        
            this->healthBar.setScale(0.5f, 0.5f);
            this->healthBar.setPosition(600, 10);
            
            int healthBarSizeInPercent = this->healthBar.getTexture()->getSize().x/100;

            this->healthBar.setTextureRect(sf::IntRect(0, 0, this->healthPoints*healthBarSizeInPercent, 50));

            window.draw(healthBarBackground);
            window.draw(healthBar);
        }

        sf::FloatRect getGlobalBounds(){
            return this->playerSprite.getGlobalBounds();
        }

        void drawPlayer(sf::RenderWindow &window){
            if (this->isCrouching) {
                this->playerTexture.loadFromFile(PLAYER_CROUCHING);

            } else if (this->xVelocity == 0) {
                this->playerTexture.loadFromFile(PLAYER[this->animationIndex]);
          
            } else if (this->xVelocity > 0) {
                if (this->isJumping) {
                    this->playerTexture.loadFromFile(PLAYER_JUMPING_RIGHT);
                } else {
                    this->playerTexture.loadFromFile(PLAYER_RIGHT_WALKING[this->animationIndex]);
                }
            } else if (this->xVelocity < 0) {
                if (this->isJumping){
                    this->playerTexture.loadFromFile(PLAYER_JUMPING_LEFT);
                } else {
                    this->playerTexture.loadFromFile(PLAYER_LEFT_WALKING[this->animationIndex]);
                }
            }

            if (animationCooldown.asSeconds() >= 0.1f) {
                animationClock.restart();
                if (this->animationIndex >= 2) {
                    this->animationIndex = 0;
                } else {
                    ++this->animationIndex;
                }
            }

            this->playerSprite.setTexture(playerTexture);
            this->playerSprite.setPosition(this->xPosition, this->yPosition);
            window.draw(this->playerSprite);

            if (this->inventory[this->selectedSlot] != 0){
                sf::Texture weaponTexture;
                sf::Sprite weaponSprite;
                float weaponXPosition = this->xPosition;
                float weaponYPosition = this->yPosition;

                if (this->inventory[this->selectedSlot] == 1){
                    weaponTexture.loadFromFile(ATTACK_WEAPON);
                    weaponTexture.setSmooth(true);
                    weaponSprite.rotate(180);
                    weaponXPosition += 90;
                    weaponYPosition += 68;
                    weaponSprite.setScale(0.2f, 0.2f);
                } else if (this->inventory[this->selectedSlot] == 2){
                    weaponTexture.loadFromFile(DEFENSE_WEAPON);
                    weaponTexture.setSmooth(true);
                    weaponXPosition += 15;
                    weaponYPosition += 30;
                    weaponSprite.setScale(0.15f, 0.15f);
                }

                weaponSprite.setTexture(weaponTexture);
                weaponSprite.setPosition(weaponXPosition, weaponYPosition);
                window.draw(weaponSprite);
            }

            animationCooldown = animationClock.getElapsedTime();
        }

        int getSelectedSlot(){
            return this->selectedSlot;
        }

        void selectSlot(){
            if (this->selectedSlot < 1) {
                ++this->selectedSlot;
            } else {
                this->selectedSlot = 0;
            }
        }

    private:
        int jumpHeight = 250;
        int score = 0;

        int maxHealth = 100;


        bool checkEnd(sf::Sprite levelEnd){
            sf::FloatRect playerBounds = this->playerSprite.getGlobalBounds();
            sf::FloatRect levelEndBounds = levelEnd.getGlobalBounds();

            if(playerBounds.intersects(levelEndBounds)){
                this->xVelocity = 0;
                this->yVelocity = 0;
                return true;
            }
            return false;
        }
   
        void gravity(sf::Sprite ground, Platform* platform){
            sf::FloatRect playerBounds = this->playerSprite.getGlobalBounds();
            sf::FloatRect platformBounds = platform->getGlobalBounds();

            float playerHeight = this->playerSprite.getTexture()->getSize().y * this->playerSprite.getScale().y;

            if(this->playerSprite.getPosition().y + playerHeight/4 < ground.getPosition().y - 20 && !this->isJumping && (!playerBounds.intersects(platformBounds) || platformBounds.contains(playerSprite.getPosition().x, playerSprite.getPosition().y + playerBounds.height-10) )){
                this->yPosition += 10;
            }
        }

        void jumping(){
            if(this->isJumping){
                if(this->yPosition <= this->originalPlayerPosition - this->jumpHeight){
                    this->isJumping = false;
                    this->jumpClock.restart();
                } else{
                    this->yPosition += this->yVelocity;
                    
                }
            }
        }
};