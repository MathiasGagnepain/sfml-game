#include <SFML/Graphics.hpp>

// standard
#include <string>
#include <iostream>

using namespace std;

// custom

#include "includes/path.hpp"

#include "class/display/Text.cc"

#include "includes/main.hpp"

#include "class/Game.cc"

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

    Weapon weapon(1, 10, false, 300, 500), shield(2, 5, true, 400, 500);
    Text text;
    Game game;


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
            else if (game.getPlayer()->levelEnded or game.getPlayer()->healthPoints <= 0){
                gameIsStarted = false;
                weapon.resetWeapon();
                shield.resetWeapon();

                game.resetGame();
            }
        }
        if (gameIsStarted && !game.getPlayer()->levelEnded && game.getPlayer()->healthPoints > 0) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::P) && keypressedCooldown.asSeconds() >= .5f){
                keypressedClock.restart();
                gameIsPaused = !gameIsPaused;
            }
            
            if(!gameIsPaused){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    game.getPlayer()->moveRight();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                    game.getPlayer()->moveLeft();
                }
                if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && !game.getPlayer()->isJumping && game.getPlayer()->getJumpCooldown().asSeconds() >= .5f){
                    game.getPlayer()->jump();
                }
                if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && game.getPlayer()->yPosition < game.getGroundPosition()[1] - 20){
                    game.getPlayer()->crouch(game.getGround());
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && keypressedCooldown.asSeconds() >= .5f){
                    keypressedClock.restart();
                    game.getPlayer()->selectSlot();

                }
            }
        }

        window.clear();

        game.moveScenery();

        game.drawGame(window);

        window.draw(text.getGameScoreText(game.getPlayer()->getScore()));


        weapon.drawWeapon(window, game.getPlayer());
        shield.drawWeapon(window, game.getPlayer());

        // Text
        if(!gameIsStarted){
            window.draw(text.getStartingText());
        } else if (game.getPlayer()->levelEnded) {
            window.draw(text.getGameEndedText());
        }
        if(gameIsPaused){
           window.draw(text.getPausedText());
        }
        if(game.getPlayer()->healthPoints <= 0){
            window.draw(text.getGameOverText());
            game.getPlayer()->xVelocity = 0;
            game.getPlayer()->yVelocity = 0;
        }
        if (game.getPlayer()->isCrouching) {
            game.getPlayer()->isCrouching = false;
        }
        
        window.display();

        keypressedCooldown = keypressedClock.getElapsedTime();
    }

    return 0;
}