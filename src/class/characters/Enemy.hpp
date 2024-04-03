//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Public Functions ●                                ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

/*
* This function is responsible for checking the collision of the player with the enemy
* @param player: the player object
* @return void
*/
void playerCollide(Player &player);

/*
* This function is responsible for the movement of the enemy
* @param void
* @return void
*/
void drawEnemy(sf::RenderWindow &window, Player &player);

/*
* This function is responsible for the resetting of the enemy
* @param void
* @return void
*/
void resetEnemy();

//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Private Functions ●                               ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

/*
* This function is responsible for the getting of the damage of the enemy
* @param void
* @return int
*/
int getDamage();

/*
* This function is responsible for the attacking of the player
* @param player: the player object
* @return void
*/
void attack(Player &player);