int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 700;

/*
* Gravity function
* @param playerSprite: sf::RectangleShape
* @param ground: sf::Sprite
* @param player: Player
* @return float
* @description: This function calculates the gravity of the player
* based on the player's position and the ground's position
* and returns the new y position of the player
*/
float gravity(sf::RectangleShape playerSprite, sf::Sprite ground, Player player);