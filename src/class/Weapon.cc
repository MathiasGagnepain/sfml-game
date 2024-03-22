#include <string>
#include <iostream>

using namespace std;


class Weapon: public Item
{
    public:
        int id;
        int damage;
        bool isDefense;
};