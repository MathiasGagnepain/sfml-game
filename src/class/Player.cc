#include <string>
#include <iostream>

using namespace std;

class Player: public Character
{
    public:
        int inventory[2];
        int score = 0;
        float xPosition = 0;
        float yPosition = 0;
        float xVelocity = 0;
        float yVelocity = 0;
        float isJumping = false;
};