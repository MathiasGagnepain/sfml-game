#pragma once

#include "Platform.cc"
#include "characters/Character.cc"
#include "characters/player.cc"
#include "characters/Enemy.cc"
#include "items/Item.cc"
#include "items/Collectable.cc"
#include "items/Weapon.cc"

class Game
{
    private:
        Platform* platform;
        Player* player;
        Enemy* enemy;
        Collectable* collectable1, *collectable2, *collectable3, *collectable4;
        sf::Texture backgroundTexture, groundTexture, levelEndTexture;
        sf::Sprite background, ground, levelEnd;
        float offsetX = 0;
        int levelSize = 3000;

        float platformsPosition[2][2] = {{700.0f, 480.0f}, {800.0f, 550.0f}}; // TODO: Not implemented yet

    public:
        /*
        * Constructor
        */
        Game();

        /*
        * Move the scenery
        * @param void
        * @return void
        */
        void moveScenery();

        /*
        * Reset the game
        * @param void
        * @return void
        */
        void resetGame();

        /*
        * Get the ground position
        * @param void
        * @return array<float, 2>
        */
        array<float, 2> getGroundPosition();

        /*
        * Get the level end position
        * @param void
        * @return array<float, 2>
        */
        sf::Sprite getGround();

        /*
        * Get the level end position
        * @param void
        * @return sf::Sprite
        */
        sf::Sprite getLevelEnd();

        /*
        * Get the player
        * @param void
        * @return Player*
        */
        Player* getPlayer();

        /*
        * Get the enemy
        * @param void
        * @return Enemy*
        */
        Enemy* getEnemy();

        /*
        * Draw the game
        * @param window : the window to draw the game on
        * @return void
        */
        void drawGame(sf::RenderWindow &window);

        /*
        * Check if the player collides with the enemy
        * @param void
        * @return void
        */
        void playerCollide();
};
