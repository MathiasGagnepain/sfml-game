#include <string>
#include <iostream>

using namespace std;


class Collectable: public Item
{
    public:
        int score;
        bool isResetter;

        void collectCoin(Player &player, int coinType){

            if(coinType == 1){
                this->score += 10;
            }else if(coinType == 2){
                this->score += 100;
            }else if(coinType == 3){
                this->score -= 50;
            }else if(coinType == 4){
                this->score = 0;
            }else {
                this->score += 0;
            }
            player.setScore(this->score);
        }

        void drawCollectable(int type, float x, float y, sf::RenderWindow &window, Player &player){
            switch (type)
            {
            case 1:
                collectableTexture.loadFromFile("../src/assets/diamond.png");
                collectable.setTexture(collectableTexture);
                collectable.setScale(.1f,.1f);
                collectable.setPosition(x, y);
                collideWithPlayer(player, type);
                break;
            case 2:
                collectableTexture.loadFromFile("../src/assets/seriglassShard.png");
                break;
            case 3:
                collectableTexture.loadFromFile("../src/assets/red_robux.png");
                break;
            case 4:
                // collectableTexture.loadFromFile("../src/assets/coin.png");
                break;
            default:
                break;
            }

            window.draw(collectable);
        }

        void collideWithPlayer(Player &player, int type){
            if(player.getGlobalBounds().intersects(collectable.getGlobalBounds())){
                collectCoin(player, type);
                collectable.setPosition(-1000, -1000);
            }
        }

    private:
        sf::Texture collectableTexture;
        sf::Sprite collectable;
};