#include "Platform.cc"
#include "characters/Character.cc"
#include "characters/player.cc"
#include "characters/Enemy.cc"
#include "items/Item.cc"
#include "items/Collectable.cc"
#include "items/Weapon.cc"

class Game
{
    private:
        Platform* platform;
        Player* player;
        Enemy* enemy;
        Collectable* collectable1, *collectable2, *collectable3, *collectable4;
        sf::Texture backgroundTexture, groundTexture, levelEndTexture;
        sf::Sprite background, ground, levelEnd;
        float offsetX = 0;
        int levelSize = 3000;

        float platformsPosition[2][2] = {{700.0f, 480.0f}, {800.0f, 550.0f}}; // TODO: Not implemented yet

    public:

        Game(){
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
            this->enemy = new Enemy(500, 500, 1);
            this->platform = new Platform(PLATFORM, 700.0f, 480.0f, 1.0f, 1.0f);

        }

        ~Game() {
            delete this->collectable1;
            delete this->collectable2;
            delete this->collectable3;
            delete this->collectable4;
            delete this->player;
            delete this->enemy;
            delete this->platform;
        }

        void moveScenery(){
            if ( (this->player->xVelocity != 0 && this->player->xPosition + this->player->xVelocity >= 500 - this->player->playerSprite.getTexture()->getSize().x * this->player->playerSprite.getScale().x) || (this->player->xVelocity != 0 && this->offsetX > 0 )){
                
                if ((this->offsetX + SCREEN_WIDTH < this->levelSize && this->player->xVelocity > 0) || (this->offsetX > 0 && this->player->xVelocity < 0 && this->player->xPosition + this->player->xVelocity <= 500 - this->player->playerSprite.getTexture()->getSize().x * this->player->playerSprite.getScale().x)){
                    this->player->xPosition = 500 - this->player->playerSprite.getTexture()->getSize().x * this->player->playerSprite.getScale().x;
                    this->platform->setPosition(this->platform->getPosition()[0] - this->player->xVelocity, this->platform->getPosition()[1]);
                    this->enemy->setPosition(this->enemy->getPosition()[0] - this->player->xVelocity, this->enemy->getPosition()[1]);
                    this->levelEnd.setPosition(this->levelEnd.getPosition().x - this->player->xVelocity, this->levelEnd.getPosition().y);

                    this->collectable1->setPosition(this->collectable1->getPosition()[0] - this->player->xVelocity, this->collectable1->getPosition()[1]);
                    this->collectable2->setPosition(this->collectable2->getPosition()[0] - this->player->xVelocity, this->collectable2->getPosition()[1]);
                    this->collectable3->setPosition(this->collectable3->getPosition()[0] - this->player->xVelocity, this->collectable3->getPosition()[1]);
                    this->collectable4->setPosition(this->collectable4->getPosition()[0] - this->player->xVelocity, this->collectable4->getPosition()[1]);

                    this->offsetX += this->player->xVelocity;
                    this->enemy->setOriginalXPosition(this->enemy->getOriginalXPosition() - this->player->xVelocity);
                }
            } else if (this->player->xPosition <= 0) {
                this->player->xPosition = 0;
            } else if (this->player->xPosition + this->player->playerSprite.getTexture()->getSize().x * this->player->playerSprite.getScale().x >= SCREEN_WIDTH) {
                this->player->xPosition = SCREEN_WIDTH - this->player->playerSprite.getTexture()->getSize().x * this->player->playerSprite.getScale().x;
            }
            this->player->physics(this->ground, this->platform, this->levelEnd);
        }

        void resetGame(){
            // gameIsStarted = false;
            this->player->levelEnded = false;
            this->player->resetPosition();
            this->player->healthPoints = 100;
            // weapon.resetWeapon();
            // shield.resetWeapon();
            this->enemy->resetEnemy();

            this->collectable1->resetCollectable();
            this->collectable2->resetCollectable();
            this->collectable3->resetCollectable();
            this->collectable4->resetCollectable();

            this->platform->setPosition(700.0f, 480.0f);
            this->enemy->setPosition(500, 500);
            this->enemy->setOriginalXPosition(500);
            this->levelEnd.setPosition(2900.0f, 570.0f);
            this->collectable1->setPosition(700, 425);
            this->collectable2->setPosition(775, 425);
            this->collectable3->setPosition(850, 425);
            this->collectable4->setPosition(950, 425);
            this->offsetX = 0;

            this->player->isJumping = false;
        }

        array<float, 2> getGroundPosition(){
            return {this->ground.getPosition().x, this->ground.getPosition().y};
        }

        sf::Sprite getGround(){
            return this->ground;
        }

        sf::Sprite getLevelEnd(){
            return this->levelEnd;
        }

        Player* getPlayer(){
            return this->player;
        }

        Enemy* getEnemy(){
            return this->enemy;
        }

        void drawGame(sf::RenderWindow &window){
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

        void playerCollide(){
            if(this->enemy->getEnemySprite().getGlobalBounds().intersects(this->player->getGlobalBounds())){
                if (this->player->inventory[this->player->selectedSlot] != 2) {
                    this->player->healthPoints -= this->enemy->getDamage();
                    this->enemy->attack(this->player);
                }
                this->player->xVelocity > 0 && this->offsetX <= 0 ? this->player->xPosition -= this->enemy->getKnockBack() : this->player->xPosition += this->enemy->getKnockBack();
                this->player->xVelocity > 0 && this->offsetX > 0 ? this->offsetX - this->enemy->getKnockBack() : this->offsetX + this->enemy->getKnockBack();
            }
        }
};
