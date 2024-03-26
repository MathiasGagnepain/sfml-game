#include <string>
#include <iostream>

using namespace std;

class Player: public Character
{
    public:
        int inventory[2];
        int score = 0;
        float xPosition = 20;
        float yPosition = 400;
        float xVelocity = 0;
        float yVelocity = 0;
        bool isJumping = false;
        float originalPlayerPosition = 0;

        string name = "Sticky";
        int healthPoints = 100;
        float baseDamage = 2;

        sf::Clock jumpClock;
        sf::Time jumpCooldown;
    
        void moveRight(){
            this->xPosition += 0.2;
        }

        void moveLeft(){
            this->xPosition -= 0.2;
        }

        void jump(){
            this->isJumping = true;
            this->originalPlayerPosition = this->yPosition;
            this->yVelocity = -0.5;
        }

        void crouch(){
            this->yPosition += 2;
        }

        void physics(sf::Sprite ground, sf::RectangleShape playerSprite){
            jumping();
            gravity(ground, playerSprite);
        }

        sf::Time getJumpCooldown(){
            return this->jumpClock.getElapsedTime(); 
        }

    private:
        void gravity(sf::Sprite ground, sf::RectangleShape playerSprite){
                if(playerSprite.getPosition().y < ground.getPosition().y - 20 && !this->isJumping){
                this->yPosition += 1;
            }
        }

        void jumping(){
            if(this->isJumping){
                if(this->yPosition <= this->originalPlayerPosition-200){
                    this->isJumping = false;
                    this->jumpClock.restart();
                } else{
                    this->yPosition += this->yVelocity;
                    
                }
            }
        }

};