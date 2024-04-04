#include <string>
#include <iostream>
#include "Text.hpp"

//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Public Functions ●                                ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

Text::Text(){
    this->font.loadFromFile(FONT);
    loadStartingText();
    loadPausedText();
    loadGameOverText();
    loadGameEndedText();
    loadGameScoreText();
}

sf::Text Text::getGameOverText(){
    return this->gameoverText;
}

sf::Text Text::getStartingText(){
    return this->startingText;
}

sf::Text Text::getPausedText(){
    return this->pauseText;
}

sf::Text Text::getGameEndedText(){
    return this->gameEndedText;
}

sf::Text Text::getGameScoreText(int score){
    this->gameScoreText.setString("Score: " + std::to_string(score));
    return this->gameScoreText;
}

//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Private Functions ●                               ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

void Text::loadGameOverText(){
    this->gameoverText.setFont(this->font);
    this->gameoverText.setString("Game Over\nPress Space to Restart");
    this->gameoverText.setCharacterSize(50);
    this->gameoverText.setFillColor(sf::Color::Red);
    this->gameoverText.setPosition(325, 300);
    this->gameoverText.setStyle(sf::Text::Underlined);
}

void Text::loadStartingText(){
    this->startingText.setFont(this->font);
    this->startingText.setString("Press Space to Start");
    this->startingText.setCharacterSize(50);
    this->startingText.setFillColor(sf::Color::Black);
    this->startingText.setPosition(325, 300);
    this->startingText.setStyle(sf::Text::Underlined);
}

void Text::loadPausedText(){
    this->pauseText.setFont(this->font);
    this->pauseText.setString("Paused - Press P to Resume");
    this->pauseText.setCharacterSize(50);
    this->pauseText.setFillColor(sf::Color::Black);
    this->pauseText.setPosition(325, 300);
    this->pauseText.setStyle(sf::Text::Underlined);
}

void Text::loadGameEndedText(){
    this->gameEndedText.setFont(this->font);
    this->gameEndedText.setString("Level completed\nPress Space to Restart");
    this->gameEndedText.setCharacterSize(50);
    this->gameEndedText.setFillColor(sf::Color::Black);
    this->gameEndedText.setPosition(325, 300);
    this->gameEndedText.setStyle(sf::Text::Underlined);
}

void Text::loadGameScoreText(){
    this->gameScoreText.setFont(this->font);
    this->gameScoreText.setString("Score: 0");
    this->gameScoreText.setCharacterSize(50);
    this->gameScoreText.setFillColor(sf::Color::Black);
    this->gameScoreText.setPosition(10, 10);
    this->gameScoreText.setStyle(sf::Text::Underlined);
}