#include <string>
#include <iostream>
#include "Weapon.hpp"

using namespace std;

//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Public Functions ●                                ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

Weapon::Weapon(int id, int damage, bool isDefense, float x, float y){
    this->id = id;
    this->damage = damage;
    this->isDefense = isDefense;
    this->weaponSprite.rotate(90);
    this->xPosition = x;
    this->yPosition = y;
}

void Weapon::drawWeapon(sf::RenderWindow &window, Player* player){
    if (this->id == 1) {
        this->weaponTexture.loadFromFile(ATTACK_WEAPON);
    } else {
        this->weaponTexture.loadFromFile(DEFENSE_WEAPON);
    }
    this->weaponSprite.setTexture(this->weaponTexture);
    this->weaponSprite.setScale(sf::Vector2f(0.2f, 0.2f));
    this->weaponSprite.setPosition(this->xPosition, this->yPosition);

    window.draw(this->weaponSprite);
    playerCollide(player);
}

void Weapon::playerCollide(Player* player){
    if(this->weaponSprite.getGlobalBounds().intersects(player->getGlobalBounds())){
        if (player->inventory[0] != 0 && player->inventory[0] != this->id) {
            player->inventory[1] = this->id;
        } else {
            player->inventory[0] = this->id;
        }
        this->weaponSprite.setPosition(-100, -100);
        this->weaponSprite.setColor(sf::Color::Transparent);
    }
}

void Weapon::resetWeapon(){
    this->weaponSprite.setPosition(this->xPosition, this->yPosition);
    this->weaponSprite.setColor(sf::Color::White);
}