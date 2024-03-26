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

        int healthPoints = 100;
        float baseDamage = 2;

        sf::Clock jumpClock;
        sf::Time jumpCooldown;

        Player(string name){
            this->name = name;
        }


        /*
        * This function is responsible for the movement of the player to the right
        * @param void
        * @return void
        */
        void moveRight(){
            this->xPosition += 0.2;
        }

        /*
        * This function is responsible for the movement of the player to the left
        * @param void
        * @return void
        */
        void moveLeft(){
            this->xPosition -= 0.2;
        }

        /*
        * This function is responsible for the jumping of the player
        * @param void
        * @return void
        */
        void jump(){
            this->isJumping = true;
            this->originalPlayerPosition = this->yPosition;
            this->yVelocity = -0.5;
        }

        /*
        * This function is responsible for the crouching of the player
        * @param void
        * @return void
        * TODO: Implement crouching
        */
        void crouch(){
            this->isJumping = false;
            this->yPosition += 2;
        }

        /*
        * This function is responsible for the physics of the player
        * @param ground: the ground sprite
        * @param playerSprite: the player sprite
        * @return void
        */
        void physics(sf::Sprite ground, sf::RectangleShape playerSprite){
            jumping();
            gravity(ground, playerSprite);
        }

        /*
        * This function is responsible for the cooldown of the jump
        * @param void
        * @return sf::Time
        */
        sf::Time getJumpCooldown(){
            return this->jumpClock.getElapsedTime(); 
        }

    private:
        int jumpHeight = 200;

        /*
        * This function is responsible for the gravity of the player
        * @param ground: the ground sprite
        * @param playerSprite: the player sprite
        * @return void
        */
        void gravity(sf::Sprite ground, sf::RectangleShape playerSprite){
                if(playerSprite.getPosition().y < ground.getPosition().y - 20 && !this->isJumping){
                this->yPosition += 1;
            }
        }

        /*
        * This function is responsible for the jumping of the player
        * @param void
        * @return void
        */
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