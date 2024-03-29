#include <string>
#include <iostream>

using namespace std;


class Collectable: public Item
{
    private:
        sf::Texture collectable1Texture, collectable2Texture, collectable3Texture, collectable4Texture;
        sf::Sprite collectable;

    public:
        int score;
        bool isEat = false;
        bool isResetter;
        int type;

        Collectable(int type){
            this->type = type;

            this->collectable1Texture.loadFromFile(COLLECTABLE1);
            this->collectable2Texture.loadFromFile(COLLECTABLE2);
            this->collectable3Texture.loadFromFile(COLLECTABLE3);
            this->collectable4Texture.loadFromFile(COLLECTABLE4);
        }

        void collectCoin(Player &player){
            this->score = player.getScore();
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
            player.setScore(this->score);
        }

        void drawCollectable(float x, float y, sf::RenderWindow &window, Player &player){

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
            this->collectable.setPosition(x, y);

            collideWithPlayer(player);

            if (this->isEat == false) {
                window.draw(this->collectable);
            }
        }

        void collideWithPlayer(Player &player){
            if(player.getGlobalBounds().intersects(collectable.getGlobalBounds()) && !this->isEat){
                this->collectable.setColor(sf::Color::Transparent);
                collectCoin(player);
                this->isEat = true;
            }
        }

        void resetCollectable(){
            this->isEat = false;
            this->collectable.setColor(sf::Color::White);
        }
};