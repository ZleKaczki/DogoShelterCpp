#include "Game.hpp"
#include <iostream>

Game::Game(sf::RenderWindow& win) : window(win) {
    // Wczytaj tło
    if (!backgroundTexture.loadFromFile("assets/background.png")) {
        std::cerr << "Nie można załadować tła\n";
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Wczytaj pieska
    if (!doggoTexture.loadFromFile("assets/kundelsoggo.png")) {
        std::cerr << "Nie można załadować psa\n";
    }
    doggoSprite.setTexture(doggoTexture);
    doggoSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    doggoSprite.setPosition(300, 300);

}

void Game::run() {
    sf::Clock clock;
    bool isRunning = true;

    while (isRunning && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                isRunning = false;
        }

        float dt = clock.restart().asSeconds();

        // Resetuj prędkość
        velocity = {0.f, 0.f};

        // Sterowanie
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            velocity.y -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            velocity.y += speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            velocity.x -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            velocity.x += speed;

        // Ruch
        doggoSprite.move(velocity * dt);

        // Animacja (jeśli się rusza)
        if (velocity != sf::Vector2f(0.f, 0.f)) {
            animationTimer += dt;
            if (animationTimer >= frameDuration) {
                frame = (frame + 1) % 2;
                doggoSprite.setTextureRect(sf::IntRect(0, frame * 64, 64, 64));
                animationTimer = 0.f;
            }
        } else {
            frame = 0;
            doggoSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
        }


        // Rysowanie
        window.clear();
        window.draw(backgroundSprite);
        window.draw(doggoSprite);
        window.display();
    }
}
