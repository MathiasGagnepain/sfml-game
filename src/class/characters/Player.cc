#include <string>
#include <iostream>
#include <array>
#include "Player.hpp"

using namespace std;

//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Public Functions ●                                ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

Player::Player(string name){
        this->name = name;

        
        this->healthBarTexture.loadFromFile(HEALTH_BAR);
        this->healthBar.setTexture(healthBarTexture);
        this->healthBarBackground.setTexture(healthBarTexture);

        // Player
        this->playerTexture.loadFromFile(PLAYER[0]);
        this->playerSprite.setTexture(playerTexture);
        this->playerSprite.setScale(sf::Vector2f(0.2f, 0.2f));
    }

void Player::resetPosition(){
    this->xPosition = 20;
    this->yPosition = 400;
    this->xVelocity = 0;
    this->yVelocity = 0;
    this->inventory[0] = 0;
    this->inventory[1] = 0;
}

void  Player::moveRight(){
    this->xVelocity = 5;
}

void  Player::moveLeft(){
    this->xVelocity = -5;
}

void  Player::jump(){
    this->isJumping = true;
    this->originalPlayerPosition = this->yPosition;
    this->yVelocity = -10;
}

void  Player::crouch(sf::Sprite ground){
    this->isJumping = false;

    float playerHeight = playerSprite.getTexture()->getSize().y * this->playerSprite.getScale().y;

    if (this->playerSprite.getPosition().y + playerHeight/4 < ground.getPosition().y - 20) {
        this->yPosition += 10;
    }

    this->isCrouching = true;
    this->xVelocity = 0;
}

void  Player::physics(sf::Sprite ground, Platform* platform, sf::Sprite levelEnd){
    if (this->xPosition <= 0 && this->xVelocity < 0){
        this->xPosition = 0;
        this->xVelocity = 0;
    } else if (this->xPosition - this->playerSprite.getTexture()->getSize().x >= SCREEN_WIDTH && this->xVelocity > 0){
        this->xPosition = SCREEN_WIDTH - this->playerSprite.getTexture()->getSize().x;
        this->xVelocity = 0;

    }
    this->xPosition += this->xVelocity;
    jumping();
    gravity(ground, platform);
    this->levelEnded = checkEnd(levelEnd);
}

sf::Time  Player::getJumpCooldown(){
    return this->jumpClock.getElapsedTime(); 
}

int  Player::getScore(){
    return this->score;
}

void  Player::setScore(int score){
    this->score = score;
}

void  Player::drawHealthBar(sf::RenderWindow &window){
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

sf::FloatRect  Player::getGlobalBounds(){
    return this->playerSprite.getGlobalBounds();
}

void  Player::drawPlayer(sf::RenderWindow &window){
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

int  Player::getSelectedSlot(){
    return this->selectedSlot;
}

void  Player::selectSlot(){
    if (this->selectedSlot < 1) {
        ++this->selectedSlot;
    } else {
        this->selectedSlot = 0;
    }
}

array<float, 2> Player::getPosition(){
    return {this->xPosition, this->yPosition};
}

void Player::setPosition(float x, float y){
    this->xPosition = x;
    this->yPosition = y;
}

int Player::getInventory(int index){
    return this->inventory[index];
}

void Player::setInventory(int index, int value){
    this->inventory[index] = value;
}

array<float, 2> Player::getVelocity(){
    return {this->xVelocity, this->yVelocity};
}

sf::Sprite Player::getPlayerSprite(){
    return this->playerSprite;
}

void Player::setLevelEnd(bool levelEnd){
    this->levelEnded = levelEnd;
}

void Player::setHealthPoints(int healthPoints){
    this->healthPoints = healthPoints;
}

int Player::getHealthPoints(){
    return this->healthPoints;
}

void Player::setIsJumping(bool isJumping){
    this->isJumping = isJumping;
}

bool Player::getIsJumping(){
    return this->isJumping;
}

bool Player::getLevelEnd(){
    return this->levelEnded;
}

void Player::setVelocity(float x, float y){
    this->xVelocity = x;
    this->yVelocity = y;
}

bool Player::getIsCrouching(){
    return this->isCrouching;
}

void Player::setIsCrouching(bool isCrouching){
    this->isCrouching = isCrouching;
}

//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Private Functions ●                               ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

bool  Player::checkEnd(sf::Sprite levelEnd){
    sf::FloatRect playerBounds = this->playerSprite.getGlobalBounds();
    sf::FloatRect levelEndBounds = levelEnd.getGlobalBounds();

    if(playerBounds.intersects(levelEndBounds)){
        this->xVelocity = 0;
        this->yVelocity = 0;
        return true;
    }
    return false;
}

void  Player::gravity(sf::Sprite ground, Platform* platform){
    sf::FloatRect playerBounds = this->playerSprite.getGlobalBounds();
    sf::FloatRect platformBounds = platform->getGlobalBounds();

    float playerHeight = this->playerSprite.getTexture()->getSize().y * this->playerSprite.getScale().y;

    if(this->playerSprite.getPosition().y + playerHeight/4 < ground.getPosition().y - 20 && !this->isJumping && (!playerBounds.intersects(platformBounds) || platformBounds.contains(playerSprite.getPosition().x, playerSprite.getPosition().y + playerBounds.height-10) )){
        this->yPosition += 10;
    }
}

void Player::jumping(){
    if(this->isJumping){
        if(this->yPosition <= this->originalPlayerPosition - this->jumpHeight){
            this->isJumping = false;
            this->jumpClock.restart();
        } else{
            this->yPosition += this->yVelocity;
            
        }
    }
}