#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 700), "SFML works!");
    sf::CircleShape shape(100.f);

    sf::Texture startScreenTexture;
    startScreenTexture.loadFromFile("../assets/start_screen.png");
    sf::Sprite startScreen;
    startScreen.setTexture(startScreenTexture);
    startScreen.setScale(1.5, 1.5);

    bool gameIsStarted = false;
    bool gameIsPaused = false;

    while (window.isOpen())
    {   
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        if (!gameIsStarted or gameIsPaused)
        {
            window.draw(startScreen);
            window.display();
            continue;
        }

        window.draw(shape);
        window.display();
    }

    return 0;
}