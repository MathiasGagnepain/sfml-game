#include <string>
#include <iostream>
#include <array>
#include "Platform.hpp"

using namespace std;

//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Public Functions ●                                ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

Platform::Platform(string path, float posX, float posY, float scaleX, float scaleY){
    this->posX = posX;
    this->posY = posY;

    this->platformTexture.loadFromFile(path);
    this->platform.setTexture(platformTexture);
    this->platform.setScale(scaleX, scaleY);
    this->platform.setPosition(posX, posY);
}

sf::FloatRect Platform::getGlobalBounds(){
    return this->platform.getGlobalBounds();
}

sf::Sprite Platform::getPlatform(){
    return this->platform;
}

array<float, 2> Platform::getPosition(){
    array<float, 2> position;
    position = {this->posX, this->posY};
    return position;
}

void Platform::setPosition(float x, float y){
    this->posX = x;
    this->posY = y;

    this->platform.setPosition(this->posX, this->posY);
}