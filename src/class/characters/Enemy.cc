#include <string>
#include <iostream>
#include "Enemy.hpp"

using namespace std;


class Enemy: public Character
{

    public:
        // 1 : Fighter, 2 : Warrior, 3 : Ranger
        int type;
        int healthPoints;

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

        void playerCollide(Player &player){
            if(this->enemySprite.getGlobalBounds().intersects(player.getGlobalBounds())){
                if (player.inventory[player.selectedSlot] != 2) {
                    player.healthPoints -= getDamage();
                    player.xVelocity > 0 ? player.xPosition -= this->knockBack : player.xPosition += this->knockBack;
                    attack(player);
                }

                cout << "Inventory Item: " << player.inventory[player.selectedSlot] << endl;

                

            }
        }

        void drawEnemy(sf::RenderWindow &window, Player &player){
            if (this->xPosition != this->originalXPosition) {
                if (this->xPosition > this->originalXPosition) {
                    this->xPosition -= 1;
                }
                else {
                    this->xPosition += 1;
                }
            }
            if (this->healthPoints > 0) {
                this->enemyTexture.loadFromFile(ENEMY);
                this->enemySprite.setTexture(this->enemyTexture);
                this->enemySprite.setScale(sf::Vector2f(0.2f, 0.2f));
                this->enemySprite.setColor(sf::Color::Red);
                this->enemySprite.setPosition(this->xPosition, this->yPosition);

                playerCollide(player);

                window.draw(this->enemySprite);
            }
        }

        void resetEnemy(){
            this->healthPoints = 10;
            this->xPosition = this->originalXPosition;
        }

    private:
        sf::Texture enemyTexture;
        sf::Sprite enemySprite;
        int knockBack = 250;
        float xPosition = 0;
        float yPosition = 0;
        float originalXPosition = 0;

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

        void attack(Player &player){

            if (player.inventory[player.selectedSlot] == 1) {
                if (this->originalXPosition == this->xPosition){
                    this->originalXPosition = this->xPosition;
                }
                this->healthPoints -= 2; //player.inventory[player.selectedSlot].damage;
                player.xVelocity > 0 ? this->xPosition += this->knockBack/4 : this->xPosition -= this->knockBack/4;
                if (this->healthPoints <= 0) {
                    player.setScore(player.getScore() + 100);
                }
                cout << "Enemy Health: " << this->healthPoints << endl;
            }
        }
};