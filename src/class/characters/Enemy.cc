#include <string>
#include <iostream>
#include "Enemy.hpp"

using namespace std;


class Enemy: public Character
{

    public:
        // 1 : Fighter, 2 : Warrior, 3 : Ranger
        int type;

        Enemy(float x, float y, int type){
            this->type = type;
            this->xPosition = x;
            this->yPosition = y;
            this->originalXPosition = x;
            if (type == 1) {
                this->healthPoints = 10;
            }
            else if (type == 2) {
                this->healthPoints = 20;
            }
            else if (type == 3) {
                this->healthPoints = 5;
            }
        }

        sf::Sprite getEnemySprite(){
            return this->enemySprite;
        }

        void drawEnemy(sf::RenderWindow &window, Player* player){
            if (this->xPosition != this->originalXPosition) {
                if (this->xPosition > this->originalXPosition) {
                    this->xPosition -= 1;
                }
                else {
                    this->xPosition += 1;
                }
            }
            if (this->healthPoints > 0) {

                if (player->xPosition < this->xPosition) {
                    this->enemyTexture.loadFromFile(ENEMY_IDLE_LEFT[this->animationIndex]);
                }
                else {
                    this->enemyTexture.loadFromFile(ENEMY_IDLE_RIGHT[this->animationIndex]);
                }
                this->enemySprite.setTexture(this->enemyTexture);
                this->enemySprite.setScale(sf::Vector2f(0.2f, 0.2f));
                this->enemySprite.setColor(sf::Color::Red);
                this->enemySprite.setPosition(this->xPosition, this->yPosition);

                window.draw(this->enemySprite);

                if (this->animationCooldown.asSeconds() >= 0.1f) {  
                    animationClock.restart();
                    if (this->animationIndex < 2) {
                        ++this->animationIndex;
                    }
                    else {
                        this->animationIndex = 0;
                    }
                }
            }

            animationCooldown = animationClock.getElapsedTime();
        }

        void resetEnemy(){
            this->healthPoints = 10;
            this->xPosition = this->originalXPosition;
        }

        void setPosition(float x, float y){
            this->xPosition = x;
            this->yPosition = y;
        }

        array<float, 2> getPosition(){
            array<float, 2> position = {this->xPosition, this->yPosition};
            return position;
        }

        int getKnockBack(){
            return this->knockBack;
        }

        void attack(Player* player){

            if (player->inventory[player->selectedSlot] == 1) {
                if (this->originalXPosition == this->xPosition){
                    this->originalXPosition = this->xPosition;
                }
                this->healthPoints -= 2; //player.inventory[player.selectedSlot].damage;
                if (this->healthPoints <= 0) {
                    player->setScore(player->getScore() + 100);
                }
            }
            player->xVelocity > 0 ? this->xPosition += this->knockBack/4 : this->xPosition -= this->knockBack/4;
        }

        int getDamage(){
            int damage = 0;
            switch (this->type)
            {
            case 1:
                damage = 2;
                break;
            case 2:
                damage = 10;
                break;
            case 3:
                damage = 5;
                break;
            default:
                break;
            }

            return damage;
        }

        int getHealthPoints(){
            return this->healthPoints;
        }

        float getOriginalXPosition(){
            return this->originalXPosition;
        }

        void setOriginalXPosition(float x){
            this->originalXPosition = x;
        }

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

        
};