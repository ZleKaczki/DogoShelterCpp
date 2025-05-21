#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <memory>
#include <vector>
#include "GameObject.hpp"


class Game {
public:
    Game(sf::RenderWindow& window);
    void run();
    bool facingRight = false;
    std::mt19937 rng;
    sf::Vector2f direction = {0.f, 0.f};
    float directionChangeTimer = 0.f;
    float directionChangeInterval = 2.0f; // co 2 sekundy losowanie nowego ruchu

private:   
    std::vector<std::shared_ptr<GameObject>> objects;
    // Lista dostępnych "klocków"
    std::vector<std::pair<std::string, sf::Sprite>> catalogIcons;
    sf::Texture bedTexture;
    
    // Do przeciągania
    bool dragging = false;
    std::string draggingType = "";
    sf::Sprite draggingSprite;

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
