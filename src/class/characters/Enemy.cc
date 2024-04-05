#include <string>
#include <iostream>
#include "Enemy.hpp"

using namespace std;

//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Public Functions ●                                ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

Enemy::Enemy(float x, float y, int type){
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

sf::Sprite Enemy::getEnemySprite(){
    return this->enemySprite;
}

void Enemy::drawEnemy(sf::RenderWindow &window, Player* player){
    if (this->xPosition != this->originalXPosition) {
        if (this->xPosition > this->originalXPosition) {
            this->xPosition -= 1;
        }
        else {
            this->xPosition += 1;
        }
    }
    if (this->healthPoints > 0) {

        if (player->getPosition()[0] < this->xPosition) {
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

void Enemy::resetEnemy(){
    this->healthPoints = 10;
    this->xPosition = this->originalXPosition;
}

void Enemy::setPosition(float x, float y){
    this->xPosition = x;
    this->yPosition = y;
}

array<float, 2> Enemy::getPosition(){
    array<float, 2> position = {this->xPosition, this->yPosition};
    return position;
}

int Enemy::getKnockBack(){
    return this->knockBack;
}

void Enemy::attack(Player* player){

    if (player->getInventory(player->getSelectedSlot()) == 1) {
        if (this->originalXPosition == this->xPosition){
            this->originalXPosition = this->xPosition;
        }
        this->healthPoints -= 2; //player.inventory[player.selectedSlot].damage;
        if (this->healthPoints <= 0) {
            player->setScore(player->getScore() + 100);
        }
    }
    player->getVelocity()[0] > 0 ? this->xPosition += this->knockBack/4 : this->xPosition -= this->knockBack/4;
}

int Enemy::getDamage(){
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

int Enemy::getHealthPoints(){
    return this->healthPoints;
}

float Enemy::getOriginalXPosition(){
    return this->originalXPosition;
}

void Enemy::setOriginalXPosition(float x){
    this->originalXPosition = x;
}