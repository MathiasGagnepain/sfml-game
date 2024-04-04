#include <string>
#include <iostream>
#include "Collectable.hpp"

using namespace std;

//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Public Functions ●                                ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

Collectable::Collectable(int type, float x, float y){
    this->type = type;
    this->xPosition = x;
    this->yPosition = y;

    this->collectable1Texture.loadFromFile(COLLECTABLE1);
    this->collectable2Texture.loadFromFile(COLLECTABLE2);
    this->collectable3Texture.loadFromFile(COLLECTABLE3);
    this->collectable4Texture.loadFromFile(COLLECTABLE4);
}

void Collectable::collectCoin(Player* player){
    this->score = player->getScore();
    if(this->type == 1){
        this->score += 10;
    }else if(this->type == 2){
        this->score += 100;
    }else if(this->type == 3){
        this->score -= 50;
    }else if(this->type == 4){
        this->score = 0;
    }else {
        this->score += 0;
    }
    player->setScore(this->score);
}

void Collectable::drawCollectable(sf::RenderWindow &window, Player* player){

    switch (this->type)
    {   
        case 1:
            this->collectable.setTexture(this->collectable1Texture);
            break;
        case 2:
            this->collectable.setTexture(this->collectable2Texture);
            break;
        case 3:
            this->collectable.setTexture(this->collectable3Texture);
            break;
        case 4:
            this->collectable.setTexture(this->collectable4Texture);
            break;
        default:
            break;
    }
    this->collectable.setScale(.1f,.1f);
    this->collectable.setPosition(this->xPosition, this->yPosition);

    collideWithPlayer(player);

    if (this->isEat == false) {
        window.draw(this->collectable);
    }
}

void Collectable::collideWithPlayer(Player* player){
    if(player->getGlobalBounds().intersects(collectable.getGlobalBounds()) && !this->isEat){
        this->collectable.setColor(sf::Color::Transparent);
        collectCoin(player);
        this->isEat = true;
    }
}

void Collectable::resetCollectable(){
    this->isEat = false;
    this->collectable.setColor(sf::Color::White);
}

void Collectable::setPosition(float x, float y){
    this->xPosition = x;
    this->yPosition = y;
}

array<float, 2> Collectable::getPosition(){
    return {this->xPosition, this->yPosition};
}
