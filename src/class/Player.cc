#include <string>
#include <iostream>

using namespace std;

class Player: public Character
{
    public:
        int inventory[2];
        float xPosition = 20;
        float yPosition = 400;
        float xVelocity = 0;
        float yVelocity = 0;
        bool isJumping = false;
        float originalPlayerPosition = 0;

        int healthPoints = 100;
        float baseDamage = 2;
        bool levelEnded = false;

        sf::Clock jumpClock;
        sf::Time jumpCooldown;

        sf::Texture healthBarTexture;
        sf::Sprite healthBar, healthBarBackground;

        Player(string name){
            this->name = name;

            
            this->healthBarTexture.loadFromFile("../src/assets/healthbar.png");
            this->healthBar.setTexture(healthBarTexture);
            this->healthBarBackground.setTexture(healthBarTexture);
        }

        void resetPosition(){
            this->xPosition = 20;
            this->yPosition = 400;
            this->xVelocity = 0;
            this->yVelocity = 0;
        }


        /*
        * This function is responsible for the movement of the player to the right
        * @param void
        * @return void
        */
        void moveRight(){
            this->xVelocity = 0.2;
        }

        /*
        * This function is responsible for the movement of the player to the left
        * @param void
        * @return void
        */
        void moveLeft(){
            this->xVelocity = -0.2;
        }

        /*
        * This function is responsible for the jumping of the player
        * @param void
        * @return void
        */
        void jump(){
            this->isJumping = true;
            this->originalPlayerPosition = this->yPosition;
            this->yVelocity = -1;
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
        void physics(sf::Sprite ground, sf::RectangleShape playerSprite, Platform platform, sf::Sprite levelEnd){
            this->xPosition += this->xVelocity;
            jumping();
            gravity(ground, playerSprite, platform);
            this->levelEnded = checkEnd(levelEnd, playerSprite);
        }

        /*
        * This function is responsible for the cooldown of the jump
        * @param void
        * @return sf::Time
        */
        sf::Time getJumpCooldown(){
            return this->jumpClock.getElapsedTime(); 
        }

        int getScore(){
            return this->score;
        }

        void setScore(int score){
            this->score = score;
        }

        sf::Sprite drawHealthBar(int type){
            if (type == 0){
                this->healthBarBackground.setScale(0.5f, 0.5f);
                this->healthBarBackground.setPosition(600, 10);
                this->healthBarBackground.setColor(sf::Color(128, 128, 128, 128));
                return this->healthBarBackground;
            } else {
                this->healthBar.setScale(0.5f, 0.5f);
                this->healthBar.setPosition(600, 10);
                this->healthBar.setTextureRect(sf::IntRect(0, 0, this->healthPoints*10, 50));
                return this->healthBar;
            }
        }

    private:
        int jumpHeight = 250;
        int score = 0;

        int maxHealth = 100;


        bool checkEnd(sf::Sprite levelEnd, sf::RectangleShape playerSprite){
            sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
            sf::FloatRect levelEndBounds = levelEnd.getGlobalBounds();

            if(playerBounds.intersects(levelEndBounds)){
                this->xVelocity = 0;
                this->yVelocity = 0;
                return true;
            }
            return false;
        }
        /*
        * This function is responsible for the gravity of the player
        * @param ground: the ground sprite
        * @param playerSprite: the player sprite
        * @return void
        */
        void gravity(sf::Sprite ground, sf::RectangleShape playerSprite, Platform platform){
            sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
            sf::FloatRect platformBounds = platform.getGlobalBounds();

            if(playerSprite.getPosition().y < ground.getPosition().y - 20 && !this->isJumping && !playerBounds.intersects(platformBounds)){
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