#include <string>
#include <iostream>

using namespace std;


class Collectable: public Item
{
    public:
        int score;
        bool isResetter;
};