#include <string>
#include <iostream>

class Text 
{
    private:
        // Text
        sf::Text startingText;
        sf::Text pauseText;
        sf::Text gameoverText;

        sf::Font font;

        void loadGameOverText(){
            this->gameoverText.setFont(this->font);
            this->gameoverText.setString("Game Over - Press Space to Restart");
            this->gameoverText.setCharacterSize(50);
            this->gameoverText.setFillColor(sf::Color::Red);
            this->gameoverText.setPosition(325, 300);
            this->gameoverText.setStyle(sf::Text::Underlined);
        }

        void loadStartingText(){
            this->startingText.setFont(this->font);
            this->startingText.setString("Press Space to Start");
            this->startingText.setCharacterSize(50);
            this->startingText.setFillColor(sf::Color::Black);
            this->startingText.setPosition(325, 300);
            this->startingText.setStyle(sf::Text::Underlined);
        }

        void loadPausedText(){
            this->pauseText.setFont(this->font);
            this->pauseText.setString("Paused - Press P to Resume");
            this->pauseText.setCharacterSize(50);
            this->pauseText.setFillColor(sf::Color::Black);
            this->pauseText.setPosition(325, 300);
            this->pauseText.setStyle(sf::Text::Underlined);
        }
    
    public:

        Text(){
            this->font.loadFromFile("../src/assets/fonts/DrawingBlood.ttf");
            loadStartingText();
            loadPausedText();
            loadGameOverText();
        }

        sf::Text getGameOverText(){
            return this->gameoverText;
        }

        sf::Text getStartingText(){
            return this->startingText;
        }

        sf::Text getPausedText(){
            return this->pauseText;
        }
};