#include "Game.hpp"
#include <iostream>
#include "Bed.hpp"

Game::Game(sf::RenderWindow& win) : window(win) {
    rng.seed(std::random_device{}());
    if (!bedTexture.loadFromFile("assets/bed.png")) {
        std::cerr << "Failed to load bed\n";
    }

    sf::Sprite icon;
    icon.setTexture(bedTexture);
    icon.setScale(0.5f, 0.5f);
    icon.setPosition(20.f, 100.f);  // pozycja w katalogu

    catalogIcons.push_back({ "Bed", icon });


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

    auto bed = std::make_shared<Bed>();
    bed->setPosition(500, 400);
    objects.push_back(bed);

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
        directionChangeTimer += dt;
        if (directionChangeTimer >= directionChangeInterval) {
            std::uniform_int_distribution<int> moveChance(0, 3); // 0: stop, 1: lewo, 2: prawo, 3: góra/dół
            int move = moveChance(rng);
        
            direction = {0.f, 0.f};
        
            switch (move) {
                case 0: // stoi
                    direction = {0.f, 0.f};
                    break;
                case 1: // lewo/prawo
                    direction.x = (rng() % 2 == 0) ? -1.f : 1.f;
                    break;
                case 2: // góra/dół
                    direction.y = (rng() % 2 == 0) ? -1.f : 1.f;
                    break;
                case 3: // po skosie
                    direction.x = (rng() % 2 == 0) ? -1.f : 1.f;
                    direction.y = (rng() % 2 == 0) ? -1.f : 1.f;
                    break;
            }
        
            directionChangeTimer = 0.f;
        }

        // Ruch
        sf::Vector2f velocity = direction * speed;
        sf::Vector2f newPos = doggoSprite.getPosition() + velocity * dt;
        sf::Vector2u windowSize = window.getSize();

        // Ogranicz do ekranu
        newPos.x = std::max(0.f, std::min(newPos.x, windowSize.x - 64.f));
        newPos.y = std::max(0.f, std::min(newPos.y, windowSize.y - 64.f));

        doggoSprite.setPosition(newPos);

        // Obrót (flip)
        if (velocity.x > 0 && !facingRight) {
            facingRight = true;
            doggoSprite.setScale(-1.f, 1.f);
            doggoSprite.setOrigin(64.f, 0.f);
        } else if (velocity.x < 0 && facingRight) {
            facingRight = false;
            doggoSprite.setScale(1.f, 1.f);
            doggoSprite.setOrigin(0.f, 0.f);
        }

        // Animacja tylko w ruchu
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

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {

            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            for (const auto& [name, icon] : catalogIcons) {
                if (icon.getGlobalBounds().contains(mousePos)) {
                    dragging = true;
                    draggingType = name;
                    draggingSprite = icon;
                    draggingSprite.setScale(1.f, 1.f);
                    draggingSprite.setOrigin(0, 0);
                    draggingSprite.setPosition(mousePos);
                }
            }
        }

        if (event.type == sf::Event::MouseMoved && dragging) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            draggingSprite.setPosition(mousePos);
        }

        if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left && dragging) {

            dragging = false;

            if (draggingType == "Bed") {
                auto bed = std::make_shared<Bed>();
                bed->setPosition(draggingSprite.getPosition().x, draggingSprite.getPosition().y);
                objects.push_back(bed);
            }

            draggingType = "";
        }




        // Rysowanie
        window.clear();
        window.draw(backgroundSprite);
        for (auto& obj : objects) {
            obj->draw(window);
        }
        // Rysuj katalog
        for (const auto& [_, icon] : catalogIcons) {
            window.draw(icon);
        }

        // Rysuj obiekty
        for (auto& obj : objects) {
            obj->draw(window);
        }

        // Rysuj przeciągany
        if (dragging) {
            window.draw(draggingSprite);
        }

        window.draw(doggoSprite);
        window.display();
    }
}
