#include <SFML/Graphics.hpp>

// standard
#include <string>
#include <iostream>

using namespace std;

// custom

#include "includes/path.h"
#include "class/Platform.cc"
#include "class/Character.cc"
#include "class/Player.cc"
#include "class/Text.cc"
// #include "class/Enemy.cc"
// #include "class/Item.cc"
// #include "class/Collectable.cc"
// #include "class/Weapon.cc"

#include "includes/main.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Stickman Exploration", sf::Style::Close | sf::Style::Titlebar);

    auto image = sf::Image{};
    if (!image.loadFromFile("../src/assets/stickman_exploration_logo.png"))
    {
        printf("Error loading icon image\n");
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    // Background
    sf::Texture backgroundTexture;
    sf::Sprite background;

    backgroundTexture.loadFromFile("../src/assets/background.png");
    background.setTexture(backgroundTexture);
    background.setScale(2.0f,2.0f);

    // Ground
    sf::Texture groundTexture;
    sf::Sprite ground;

    groundTexture.loadFromFile("../src/assets/ground.png");
    ground.setTexture(groundTexture);
    ground.setScale(2.0f,1.0f);
    ground.setPosition(0.0f, 600.0f);

    // Level End
    sf::Texture levelEndTexture;
    sf::Sprite levelEnd;
    levelEndTexture.loadFromFile("../src/assets/end.png");
    levelEnd.setTexture(levelEndTexture);
    levelEnd.setScale(.2f,.2f);
    levelEnd.setPosition(1100.0f, 570.0f);



    // Platform
    Platform platform("../src/assets/platform.png", 700.0f, 480.0f, 1.0f, .75f);
    
    // Player
    sf::RectangleShape playerSprite(sf::Vector2f(75.0f, 100.0f));
    playerSprite.setFillColor(sf::Color::Red);

    Player player("Sticky");
    Text text;

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

        // Keyboard Events
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ 
            if(!gameIsStarted){
                gameIsStarted = true;
            }
            else if (player.levelEnded){
                gameIsStarted = false;
                player.levelEnded = false;
                player.resetPosition();
            }
        }
        if (gameIsStarted && !player.levelEnded && player.healthPoints > 0) {
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
                    player.crouch();
                }
            }
        }

        window.clear();
        
        player.physics(ground, playerSprite, platform, levelEnd);

        playerSprite.setPosition(player.xPosition, player.yPosition);

        window.draw(background);
        window.draw(ground);
        window.draw(platform.getPlatform());
        window.draw(levelEnd);
        window.draw(text.getGameScoreText(player.getScore()));

        window.draw(playerSprite);

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
        }
        
        window.display();

        pauseCooldown = pauseClock.getElapsedTime();
    }

    return 0;
}