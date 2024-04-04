#include "class/items/Item.cc"
#include "class/items/Collectable.cc"
#include "class/items/Weapon.cc"

class Game
{
    private:
        Collectable collectable1, collectable2, collectable3, collectable4;

    public:

        Game() : collectable1(1, 700, 425), collectable2(2, 775, 425), collectable3(3, 850, 425), collectable4(4, 950, 425) {}

        void moveScenery(sf::RenderWindow &window, Platform &platform, Player &player, Enemy &enemy, sf::Sprite &endLevel){
            if (player.xVelocity != 0 && player.xPosition + player.xVelocity >= 500 - player.playerSprite.getTexture()->getSize().x * player.playerSprite.getScale().x){
                player.xPosition = 500 - player.playerSprite.getTexture()->getSize().x * player.playerSprite.getScale().x;
                platform.setPosition(platform.getPosition()[0] - 1, platform.getPosition()[1]);
                enemy.setPosition(enemy.getPosition()[0] - 1, enemy.getPosition()[1]);
                endLevel.setPosition(endLevel.getPosition().x - 1, endLevel.getPosition().y);

                // TODO: refactor this
                collectable1.setPosition(collectable1.getPosition()[0] - 1, collectable1.getPosition()[1]);
                collectable2.setPosition(collectable2.getPosition()[0] - 1, collectable2.getPosition()[1]);
                collectable3.setPosition(collectable3.getPosition()[0] - 1, collectable3.getPosition()[1]);
                collectable4.setPosition(collectable4.getPosition()[0] - 1, collectable4.getPosition()[1]);

                player.offsetX += 1;
            } else if (player.xVelocity != 0 && player.offsetX > 0){
                player.xPosition = 500 - player.playerSprite.getTexture()->getSize().x * player.playerSprite.getScale().x;
                platform.setPosition(platform.getPosition()[0] + 1, platform.getPosition()[1]);
                enemy.setPosition(enemy.getPosition()[0] + 1, enemy.getPosition()[1]);
                endLevel.setPosition(endLevel.getPosition().x + 1, endLevel.getPosition().y);
                
                // TODO: refactor this
                collectable1.setPosition(collectable1.getPosition()[0] + 1, collectable1.getPosition()[1]);
                collectable2.setPosition(collectable2.getPosition()[0] + 1, collectable2.getPosition()[1]);
                collectable3.setPosition(collectable3.getPosition()[0] + 1, collectable3.getPosition()[1]);
                collectable4.setPosition(collectable4.getPosition()[0] + 1, collectable4.getPosition()[1]);

                player.offsetX -= 1;
            } else if (player.xPosition <= 0) {
                player.xPosition = 0;
            }
            
        }

        void resetGame(){
            this->collectable1.resetCollectable();
            this->collectable2.resetCollectable();
            this->collectable3.resetCollectable();
            this->collectable4.resetCollectable();
        }

        void drawGame(sf::RenderWindow &window, Player &player){
            this->collectable1.drawCollectable(window, player);
            this->collectable2.drawCollectable(window, player);
            this->collectable3.drawCollectable(window, player);
            this->collectable4.drawCollectable(window, player);
        }
};
