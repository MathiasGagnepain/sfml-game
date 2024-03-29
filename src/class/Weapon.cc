#include <string>
#include <iostream>

using namespace std;


class Weapon: public Item
{
    private:
        sf::Texture weaponTexture;
        sf::Sprite weaponSprite;

    public:
        int id;
        int damage;
        bool isDefense;

        Weapon(int id, int damage, bool isDefense){
            this->id = id;
            this->damage = damage;
            this->isDefense = isDefense;
            this->weaponSprite.rotate(90);
        }

        void attack(Enemy &enemy){
            enemy.healthPoints -= this->damage;
        }

        void drawWeapon(float x, float y, sf::RenderWindow &window, Player &player){
            this->weaponTexture.loadFromFile(ATTACK_WEAPON);
            this->weaponSprite.setTexture(this->weaponTexture);
            this->weaponSprite.setScale(sf::Vector2f(0.2f, 0.2f));
            this->weaponSprite.setPosition(x, y);

            window.draw(this->weaponSprite);
            playerCollide(player);
        }

        void playerCollide(Player &player){
            if(this->weaponSprite.getGlobalBounds().intersects(player.getGlobalBounds())){
                player.inventory[0] = this->id;
                this->weaponSprite.setPosition(-100, -100);
                this->weaponSprite.setColor(sf::Color::Transparent);
            }
        }


};