#include <SFML/Graphics.hpp>

// standard
#include <string>
#include <iostream>

using namespace std;

// custom

#include "includes/path.hpp"
#include "class/Platform.cc"
#include "class/characters/Character.cc"
#include "class/characters/Player.cc"
#include "class/characters/Enemy.cc"
#include "class/display/Text.cc"
#include "class/items/Item.cc"
#include "class/items/Collectable.cc"
#include "class/items/Weapon.cc"


#include "includes/main.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Stickman Exploration", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    auto image = sf::Image{};
    if (!image.loadFromFile(LOGO))
    {
        printf("Error loading icon image\n");
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    // Background
    sf::Texture backgroundTexture;
    sf::Sprite background;

    backgroundTexture.loadFromFile(BACKGROUND);
    background.setTexture(backgroundTexture);
    background.setScale(2.0f,2.0f);

    // Ground
    sf::Texture groundTexture;
    sf::Sprite ground;

    groundTexture.loadFromFile(GROUND);
    ground.setTexture(groundTexture);
    ground.setScale(2.0f,1.0f);
    ground.setPosition(0.0f, 600.0f);

    // Level End
    sf::Texture levelEndTexture;
    sf::Sprite levelEnd;
    levelEndTexture.loadFromFile(LEVEL_END);
    levelEnd.setTexture(levelEndTexture);
    levelEnd.setScale(.2f,.2f);
    levelEnd.setPosition(1100.0f, 570.0f);

    // Platform
    Platform platform(PLATFORM, 700.0f, 480.0f, 1.0f, .75f);

    Enemy enemy(500, 500, 1);
    Player player("Sticky");
    Weapon weapon(1, 10, false, 300, 500), shield(2, 5, true, 400, 500);
    Text text;

    Collectable collectable1(1), collectable2(2), collectable3(3), collectable4(4);

    bool gameIsStarted = false;
    bool gameIsPaused = false;

    sf::Clock keypressedClock;
    sf::Time keypressedCooldown;

    while (window.isOpen())
    {   
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Keyboard Events
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ 
            if(!gameIsStarted){
                gameIsStarted = true;
            }
            else if (player.levelEnded or player.healthPoints <= 0){
                gameIsStarted = false;
                player.levelEnded = false;
                player.resetPosition();
                player.healthPoints = 100;
                collectable1.resetCollectable();
                collectable2.resetCollectable();
                collectable3.resetCollectable();
                collectable4.resetCollectable();
                weapon.resetWeapon();
                shield.resetWeapon();
                enemy.resetEnemy();
            }
        }
        if (gameIsStarted && !player.levelEnded && player.healthPoints > 0) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::P) && keypressedCooldown.asSeconds() >= .5f){
                keypressedClock.restart();
                gameIsPaused = !gameIsPaused;
            }
            
            if(!gameIsPaused){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    player.moveRight();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                    player.moveLeft();
                }
                if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && !player.isJumping && player.getJumpCooldown().asSeconds() >= .5f){
                    player.jump();
                }
                if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && player.yPosition < ground.getPosition().y - 20){
                    player.crouch(ground);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && keypressedCooldown.asSeconds() >= .5f){
                    keypressedClock.restart();
                    player.selectSlot();

                }
            }
        }

        window.clear();
        
        player.physics(ground, platform, levelEnd);

        window.draw(background);
        window.draw(ground);
        window.draw(platform.getPlatform());
        window.draw(levelEnd);
        window.draw(text.getGameScoreText(player.getScore()));


        player.drawHealthBar(window);

        player.drawPlayer(window);

        collectable1.drawCollectable(700, 425, window, player);
        collectable2.drawCollectable(775, 425, window, player);
        collectable3.drawCollectable(850, 425, window, player);
        collectable4.drawCollectable(950, 425, window, player);

        enemy.drawEnemy(window, player);
        weapon.drawWeapon(window, player);
        shield.drawWeapon(window, player);

        // Text
        if(!gameIsStarted){
            window.draw(text.getStartingText());
        } else if (player.levelEnded) {
            window.draw(text.getGameEndedText());
        }
        if(gameIsPaused){
           window.draw(text.getPausedText());
        }
        if(player.healthPoints <= 0){
            window.draw(text.getGameOverText());
            player.xVelocity = 0;
            player.yVelocity = 0;
        }
        if (player.isCrouching) {
            player.isCrouching = false;
        }
        
        window.display();

        keypressedCooldown = keypressedClock.getElapsedTime();
    }

    return 0;
}