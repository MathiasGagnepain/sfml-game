#pragma once

#include <string>
#include <iostream>

class Text 
{
    private:
        // Text
        sf::Text startingText;
        sf::Text pauseText;
        sf::Text gameoverText;
        sf::Text gameEndedText;
        sf::Text gameScoreText;

        sf::Font font;

        /*
        * Load the game over text
        * @param void
        * @return void
        */
        void loadGameOverText();

        /*
        * Load the starting text
        * @param void
        * @return void
        */
        void loadStartingText();

        /*
        * Load the paused text
        * @param void
        * @return void
        */
        void loadPausedText();
    
        /*
        * Load the game ended text
        * @param void
        * @return void
        */
        void loadGameEndedText();

        /*
        * Load the game score text
        * @param void
        * @return void
        */
        void loadGameScoreText();

    public:

        /*
        * Constructor
        */
        Text();

        /*
        * the function returns the game over text
        * @param void
        * @return sf::Text
        */
        sf::Text getGameOverText();

        /*
        * the function returns the starting text
        * @param void
        * @return sf::Text
        */
        sf::Text getStartingText();

        /*
        * the function returns the paused text
        * @param void
        * @return sf::Text
        */
        sf::Text getPausedText();

        /*
        * the function returns the game ended text
        * @param void
        * @return sf::Text
        */
        sf::Text getGameEndedText();

        /*
        * the function returns the game score text
        * @param score : the score of the game
        * @return sf::Text
        */
        sf::Text getGameScoreText(int score);
};