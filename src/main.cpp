#include <SFML/Graphics.hpp>

// standard
#include <string>
#include <iostream>

using namespace std;

// custom

#include "class/Character.cc"
#include "class/Player.cc"
// #include "class/Enemy.cc"
// #include "class/Item.cc"
// #include "class/Collectable.cc"
// #include "class/Weapon.cc"

#include "includes/main.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Stickman Exploration");

    // Background
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../src/assets/background.png");
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setScale(2.0f,2.0f);

    // Ground
    sf::Texture groundTexture;
    groundTexture.loadFromFile("../src/assets/ground.png");
    sf::Sprite ground;
    ground.setTexture(groundTexture);
    ground.setScale(2.0f,1.0f);
    ground.setPosition(0.0f, 600.0f);

    // Text
    sf::Text text;
    sf::Font font;
    font.loadFromFile("../src/assets/fonts/DrawingBlood.ttf");
    text.setFont(font);
    text.setString("Press Space to Start");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Black);
    text.setPosition(400, 300);
    text.setStyle(sf::Text::Underlined);

    sf::Text text2;
    text2.setFont(font);
    text2.setString("Paused - Press P to Resume");
    text2.setCharacterSize(50);
    text2.setFillColor(sf::Color::Black);
    text2.setPosition(400, 300);
    text2.setStyle(sf::Text::Underlined);

    sf::Text gameoverText;
    gameoverText.setFont(font);
    gameoverText.setString("Game Over - Press Space to Restart");
    gameoverText.setCharacterSize(50);
    gameoverText.setFillColor(sf::Color::Red);
    gameoverText.setPosition(400, 300);
    gameoverText.setStyle(sf::Text::Underlined);
    

    // Player
    sf::RectangleShape playerSprite(sf::Vector2f(75.0f, 100.0f));
    playerSprite.setFillColor(sf::Color::Red);

    Player player;


    bool gameIsStarted = false;
    bool gameIsPaused = false;

    sf::Clock pauseClock;
    sf::Time pauseCooldown;

    while (window.isOpen())
    {   
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if(!gameIsStarted){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                gameIsStarted = true;
            }
        } else{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::P) && pauseCooldown.asSeconds() >= .5f){
                pauseClock.restart();
                gameIsPaused = !gameIsPaused;
            }
            
            if(!gameIsPaused){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    player.moveRight();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    player.moveLeft();
                }
                if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && !player.isJumping && player.getJumpCooldown().asSeconds() >= .5f){
                    player.jump();
                }
                if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && player.yPosition < ground.getPosition().y - 20){
                    player.isJumping = false;
                    player.crouch();
                }
            }
        }

        window.clear();
        
        player.physics(ground, playerSprite);

        playerSprite.setPosition(player.xPosition, player.yPosition);

        window.draw(background);
        window.draw(ground);
        window.draw(playerSprite);
        if(!gameIsStarted){
            window.draw(text);
        }
        if(gameIsPaused){
            window.draw(text2);
        }
        if(player.healthPoints <= 0){
            window.draw(gameoverText);
        }
        window.display();

        pauseCooldown = pauseClock.getElapsedTime();
    }

    return 0;
}