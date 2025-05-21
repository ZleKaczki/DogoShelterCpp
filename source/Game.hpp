#pragma once
#include <SFML/Graphics.hpp>

class Game {
public:
    Game(sf::RenderWindow& window);
    void run();

private:
    sf::RenderWindow& window;

    // Grafika
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture doggoTexture;
    sf::Sprite doggoSprite;

    // Ruch i animacja
    sf::Vector2f velocity;
    float speed = 200.0f; // px/s

    // Animacja
    int frame = 0;
    float animationTimer = 0.0f;
    float frameDuration = 0.2f; // sekundy na klatkę
};
