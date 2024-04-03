//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Public Functions ●                                ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

    /*
    * This function is responsible for the getting of the health points
    * @param void
    * @return int
    */
    void resetPosition();

    /*
    * This function is responsible for the movement of the player to the right
    * @param void
    * @return void
    */
    void moveRight();

    /*
    * This function is responsible for the movement of the player to the left
    * @param void
    * @return void
    */
    void moveLeft();

    /*
    * This function is responsible for the jumping of the player
    * @param void
    * @return void
    */
    void jump();

    /*
    * This function is responsible for the crouching of the player
    * @param ground: the ground sprite
    * @return void
    */
    void crouch(sf::Sprite ground);

    /*
    * This function is responsible for the physics of the player
    * @param ground: the ground sprite
    * @param platform: the platform sprite
    * @param levelEnd: the level end sprite
    * @return void
    */
    void physics(sf::Sprite ground, Platform platform, sf::Sprite levelEnd);

    /*
    * This function is responsible for the cooldown of the jump
    * @param void
    * @return sf::Time
    */
    sf::Time getJumpCooldown();

    /*
    * This function is responsible for the getting of the score
    * @param void
    * @return int
    */
    int getScore();

    /*
    * This function is responsible for the setting of the score
    * @param score: the score to set
    * @return void
    */
    void setScore(int score);

    /*
    * This function is responsible for the drawing of the health bar
    * @param window: the window to draw the health bar
    * @return void
    */
    void drawHealthBar(sf::RenderWindow &window);


    /*
    * This function is responsible for the getting of the global bounds of the player
    * @param void
    * @return sf::FloatRect
    */
    sf::FloatRect getGlobalBounds();

    /*
    * This function is responsible for the updating of the player position
    * @param void
    * @return void
    */
    void updatePlayerPosition();

    /*
    * This function is responsible for the drawing of the player
    * @param window: the window to draw the player
    * @return void
    */
    void drawPlayer(sf::RenderWindow &window);

    /*
    * This function is responsible for the getting of the selected slot
    * @param void
    * @return int
    */
    int getSelectedSlot();

    /*
    * This function is responsible for the selecting of the inventory slot
    * @param void
    * @return void
    */
    void selectSlot();


//  ╔══════════════════════════════════════════════════════════════════════════════╗
//  ║                          ● Private Functions ●                               ║
//  ║                                                                              ║
//  ║                             • • • • • • • •                                  ║
//  ╚══════════════════════════════════════════════════════════════════════════════╝

/*
* This function is responsible of checking if the player collide with the end of the level
* @param levelEnd: the end of the level sprite
* @return bool
*/
bool checkEnd(sf::Sprite levelEnd);

/*
* This function is responsible for the gravity of the player
* @param ground: the ground sprite
* @param platform: the platform sprite
* @return void
*/
void gravity(sf::Sprite ground, Platform platform);

/*
* This function is responsible for the jumping of the player
* @param void
* @return void
*/
void jumping();