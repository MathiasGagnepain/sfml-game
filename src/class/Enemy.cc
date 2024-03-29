#include <string>
#include <iostream>

using namespace std;


class Enemy: public Character
{
    private:
        sf::Texture enemyTexture;
        sf::Sprite enemySprite;
        int knockBack = 250;

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

    public:
        // 1 : Fighter, 2 : Warrior, 3 : Ranger
        int type;

    Enemy(int type){
        this->type = type;
    }

    void playerCollide(Player &player){
        if(this->enemySprite.getGlobalBounds().intersects(player.getGlobalBounds())){
            player.healthPoints -= getDamage();

            player.xVelocity > 0 ? player.xPosition -= this->knockBack : player.xPosition += this->knockBack;

        }
    }

    void drawEnemy(float x, float y, sf::RenderWindow &window, Player &player){
        
        this->enemyTexture.loadFromFile(ENEMY);
        this->enemySprite.setTexture(this->enemyTexture);
        this->enemySprite.setScale(sf::Vector2f(0.2f, 0.2f));
        this->enemySprite.setColor(sf::Color::Red);
        this->enemySprite.setPosition(x, y);

        playerCollide(player);

        window.draw(this->enemySprite);
    }
};