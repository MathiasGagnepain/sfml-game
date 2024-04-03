//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Public Functions ●                                ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

/*
* This function is responsible for the drawing of the weapon
* @param window: the window to draw the weapon
* @param player: the player object
* @return void
*/
void drawWeapon(sf::RenderWindow &window, Player &player);

/*
* This function is responsible for the collision of the player with the weapon
* @param player: the player object
* @return void
*/
void playerCollide(Player &player);

/*
* This function is responsible for the resetting of the weapon
* @param void
* @return void
*/
void resetWeapon();

//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Private Functions ●                               ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

