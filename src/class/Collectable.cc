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
            else {
                this->score += 0;
            }
            player.score += this->score;
        }

    private:
        sf::Texture collectableTexture;
        sf::Sprite collectable;
};