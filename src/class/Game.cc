#include "Game.hpp"

//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Public Functions ●                                ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

Game::Game(){
    this->backgroundTexture.loadFromFile(BACKGROUND);
    this->background.setTexture(backgroundTexture);
    this->background.setScale(2.0f,2.0f);

    this->groundTexture.loadFromFile(GROUND);
    this->ground.setTexture(groundTexture);
    this->ground.setScale(2.0f,1.0f);
    this->ground.setPosition(0.0f, 600.0f);

    this->levelEndTexture.loadFromFile(LEVEL_END);
    this->levelEnd.setTexture(levelEndTexture);
    this->levelEnd.setScale(.2f,.2f);
    this->levelEnd.setPosition(2900.0f, 570.0f);

    this->collectable1 = new Collectable(1, 700, 425);
    this->collectable2 = new Collectable(2, 775, 425);
    this->collectable3 = new Collectable(3, 850, 425);
    this->collectable4 = new Collectable(4, 950, 425);

    this->player = new Player("Sticky");
    this->enemy = new Enemy(1200, this->ground.getPosition().y - 40, 1);
    this->platform = new Platform(PLATFORM, 700.0f, 480.0f, 1.0f, 0.75f);

}

void Game::moveScenery(){
    if ( (this->player->getVelocity()[0] != 0 && this->player->getPosition()[0] + this->player->getVelocity()[0] >= 500 - this->player->getPlayerSprite().getTexture()->getSize().x * this->player->getPlayerSprite().getScale().x) || (this->player->getVelocity()[0] != 0 && this->offsetX > 0 )){
        
        if ((this->offsetX + SCREEN_WIDTH < this->levelSize && this->player->getVelocity()[0] > 0) || (this->offsetX > 0 && this->player->getVelocity()[0] < 0 && this->player->getPosition()[0] + this->player->getVelocity()[0] <= 500 - this->player->getPlayerSprite().getTexture()->getSize().x * this->player->getPlayerSprite().getScale().x)){
            this->player->setPosition(500 - this->player->getPlayerSprite().getTexture()->getSize().x * this->player->getPlayerSprite().getScale().x, this->player->getPosition()[1]);
            this->platform->setPosition(this->platform->getPosition()[0] - this->player->getVelocity()[0], this->platform->getPosition()[1]);
            this->enemy->setPosition(this->enemy->getPosition()[0] - this->player->getVelocity()[0], this->enemy->getPosition()[1]);
            this->levelEnd.setPosition(this->levelEnd.getPosition().x - this->player->getVelocity()[0], this->levelEnd.getPosition().y);

            this->collectable1->setPosition(this->collectable1->getPosition()[0] - this->player->getVelocity()[0], this->collectable1->getPosition()[1]);
            this->collectable2->setPosition(this->collectable2->getPosition()[0] - this->player->getVelocity()[0], this->collectable2->getPosition()[1]);
            this->collectable3->setPosition(this->collectable3->getPosition()[0] - this->player->getVelocity()[0], this->collectable3->getPosition()[1]);
            this->collectable4->setPosition(this->collectable4->getPosition()[0] - this->player->getVelocity()[0], this->collectable4->getPosition()[1]);

            this->offsetX += this->player->getVelocity()[0];
            this->enemy->setOriginalXPosition(this->enemy->getOriginalXPosition() - this->player->getVelocity()[0]);
        }
    } else if (this->player->getPosition()[0] <= 0) {
        this->player->setPosition(0, this->player->getPosition()[1]);
    } else if (this->player->getPosition()[0] + this->player->getPlayerSprite().getTexture()->getSize().x * this->player->getPlayerSprite().getScale().x >= SCREEN_WIDTH) {
        this->player->setPosition(SCREEN_WIDTH - this->player->getPlayerSprite().getTexture()->getSize().x * this->player->getPlayerSprite().getScale().x, this->player->getPosition()[1]);
    }
    this->player->physics(this->ground, this->platform, this->levelEnd);
}

void Game::resetGame(){
    // gameIsStarted = false;
    this->player->setLevelEnd(false);
    this->player->resetPosition();
    this->player->setHealthPoints(100);
    // weapon.resetWeapon();
    // shield.resetWeapon();
    this->enemy->resetEnemy();

    this->collectable1->resetCollectable();
    this->collectable2->resetCollectable();
    this->collectable3->resetCollectable();
    this->collectable4->resetCollectable();

    this->platform->setPosition(700.0f, 480.0f);
    this->enemy->setPosition(1200, this->ground.getPosition().y - 40);
    this->enemy->setOriginalXPosition(1200);
    this->levelEnd.setPosition(2900.0f, 570.0f);
    this->collectable1->setPosition(700, 425);
    this->collectable2->setPosition(775, 425);
    this->collectable3->setPosition(850, 425);
    this->collectable4->setPosition(950, 425);
    this->offsetX = 0;

    this->player->setIsJumping(false);
}

array<float, 2> Game::getGroundPosition(){
    return {this->ground.getPosition().x, this->ground.getPosition().y};
}

sf::Sprite Game::getGround(){
    return this->ground;
}

sf::Sprite Game::getLevelEnd(){
    return this->levelEnd;
}

Player* Game::getPlayer(){
    return this->player;
}

Enemy* Game::getEnemy(){
    return this->enemy;
}

void Game::drawGame(sf::RenderWindow &window){
    window.draw(this->background);
    window.draw(ground);

    window.draw(this->platform->getPlatform());
    window.draw(levelEnd);

    this->collectable1->drawCollectable(window, this->player);
    this->collectable2->drawCollectable(window, this->player);
    this->collectable3->drawCollectable(window, this->player);
    this->collectable4->drawCollectable(window, this->player);

    this->enemy->drawEnemy(window, this->player);
    if (this->enemy->getHealthPoints()) {
        this->playerCollide();
    }
    this->player->drawPlayer(window);
    
    // HUD
    this->player->drawHealthBar(window);
}

void Game::playerCollide(){
    if(this->enemy->getEnemySprite().getGlobalBounds().intersects(this->player->getGlobalBounds())){
        if (this->player->getInventory(this->player->getSelectedSlot()) != 2) {
            this->player->setHealthPoints(this->player->getHealthPoints() - this->enemy->getDamage());
            this->enemy->attack(this->player);
        }
        this->player->getVelocity()[0] > 0 && this->offsetX <= 0 ? this->player->getPosition()[0] -= this->enemy->getKnockBack() : this->player->getPosition()[0] += this->enemy->getKnockBack();
        this->player->getVelocity()[0] > 0 && this->offsetX > 0 ? this->offsetX - this->enemy->getKnockBack() : this->offsetX + this->enemy->getKnockBack();
    }
}