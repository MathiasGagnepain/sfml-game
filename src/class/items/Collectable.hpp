//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Public Functions ●                                ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

/*
* This function is responsible for the collection of the coin
* @param player: the player object
* @return void
*/
void collectCoin(Player &player);

/*
* This function is responsible for the drawing of the collectable
* @param x: the x position of the collectable
* @param y: the y position of the collectable
* @param window: the window to draw the collectable
* @param player: the player object
* @return void
*/
void drawCollectable(float x, float y, sf::RenderWindow &window, Player &player);

/*
* This function is responsible for the collision of the player with the collectable
* @param player: the player object
* @return void
*/
void collideWithPlayer(Player &player);

/*
* This function is responsible for the resetting of the collectable
* @param void
* @return void
*/
void resetCollectable();

//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Private Functions ●                               ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

