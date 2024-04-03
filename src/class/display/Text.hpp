//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Public Functions ●                                ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

/*
* This function is responsible for the setting of the game over text
* @param void
* @return void
*/
sf::Text getGameOverText();

/*
* This function is responsible for the setting of the starting text
* @param void
* @return void
*/
sf::Text getStartingText();

/*
* This function is responsible for the setting of the paused text
* @param void
* @return void
*/
sf::Text getPausedText();

/*
* This function is responsible for the setting of the game ended text
* @param void
* @return void
*/
sf::Text getGameEndedText();

/*
* This function is responsible for the setting of the game score text
* @param score: the score of the game
* @return void
*/
sf::Text getGameScoreText(int score);

//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Private Functions ●                               ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

/*
* This function is responsible for the loading of the game over text
* @param void
* @return void
*/
void loadGameOverText();

/*
* This function is responsible for the loading of the starting text
* @param void
* @return void
*/
void loadStartingText();

/*
* This function is responsible for the loading of the paused text
* @param void
* @return void
*/
void loadPausedText();

/*
* This function is responsible for the loading of the game ended text
* @param void
* @return void
*/
void loadGameEndedText();

/*
* This function is responsible for the loading of the game score text
* @param void
* @return void
*/
void loadGameScoreText();