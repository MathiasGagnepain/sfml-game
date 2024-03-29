#include <string>
#include <iostream>

using namespace std;

class Player: public Character
{
    public:
        int inventory[2];
        float xPosition = 20;
        float yPosition = 0;
        float xVelocity = 0;
        float yVelocity = 0;
        bool isJumping = false;
        float originalPlayerPosition = 0;

        int healthPoints = 100;
        float baseDamage = 2;
        bool levelEnded = false;

        sf::Clock jumpClock;
        sf::Time jumpCooldown;

        sf::Texture healthBarTexture, playerTexture;
        sf::Sprite healthBar, healthBarBackground, playerSprite;

        // sf::Vector2f(75.0f, 100.0f)

        Player(string name){
            this->name = name;

            
            this->healthBarTexture.loadFromFile("../src/assets/healthbar.png");
            this->healthBar.setTexture(healthBarTexture);
            this->healthBarBackground.setTexture(healthBarTexture);

            // Player
            this->playerTexture.loadFromFile("../src/assets/stickman.png");
            this->playerSprite.setTexture(playerTexture);
            this->playerSprite.setScale(sf::Vector2f(0.2f, 0.2f));
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
            this->xVelocity = 5;
        }

        /*
        * This function is responsible for the movement of the player to the left
        * @param void
        * @return void
        */
        void moveLeft(){
            if (this->xPosition > 0) {
                this->xVelocity = -5;
            }
        }

        /*
        * This function is responsible for the jumping of the player
        * @param void
        * @return void
        */
        void jump(){
            this->isJumping = true;
            this->originalPlayerPosition = this->yPosition;
            this->yVelocity = -10;
        }

        /*
        * This function is responsible for the crouching of the player
        * @param void
        * @return void
        * TODO: Implement crouching
        */
        void crouch(sf::Sprite ground){
            this->isJumping = false;

            float playerHeight = playerSprite.getTexture()->getSize().y * this->playerSprite.getScale().y;

            if (this->playerSprite.getPosition().y + playerHeight/4 < ground.getPosition().y - 20) {
                this->yPosition += 10;
            }
        }

        /*
        * This function is responsible for the physics of the player
        * @param ground: the ground sprite
        * @return void
        */
        void physics(sf::Sprite ground, Platform platform, sf::Sprite levelEnd){
            this->xPosition += this->xVelocity;
            jumping();
            gravity(ground, platform);
            this->levelEnded = checkEnd(levelEnd);
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

        void drawHealthBar(sf::RenderWindow &window){
            this->healthBarBackground.setScale(0.5f, 0.5f);
            this->healthBarBackground.setPosition(600, 10);
            this->healthBarBackground.setColor(sf::Color(128, 128, 128, 128));
        
            this->healthBar.setScale(0.5f, 0.5f);
            this->healthBar.setPosition(600, 10);
            this->healthBar.setTextureRect(sf::IntRect(0, 0, this->healthPoints*10, 50));

            window.draw(healthBarBackground);
            window.draw(healthBar);
        }

        sf::FloatRect getGlobalBounds(){
            return this->playerSprite.getGlobalBounds();
        }

        void updatePlayerPosition(){
            this->playerSprite.setPosition(this->xPosition, this->yPosition);
        }

        void drawPlayer(sf::RenderWindow &window){
            this->playerSprite.setPosition(this->xPosition, this->yPosition);
            window.draw(this->playerSprite);
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
        /*
        * This function is responsible for the gravity of the player
        * @param ground: the ground sprite
        * @return void
        */
        void gravity(sf::Sprite ground, Platform platform){
            sf::FloatRect playerBounds = this->playerSprite.getGlobalBounds();
            sf::FloatRect platformBounds = platform.getGlobalBounds();

            float playerHeight = this->playerSprite.getTexture()->getSize().y * this->playerSprite.getScale().y;

            if(this->playerSprite.getPosition().y + playerHeight/4 < ground.getPosition().y - 20 && !this->isJumping && (!playerBounds.intersects(platformBounds) || platformBounds.contains(playerSprite.getPosition().x, playerSprite.getPosition().y + playerBounds.height-10) )){
                this->yPosition += 10;
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