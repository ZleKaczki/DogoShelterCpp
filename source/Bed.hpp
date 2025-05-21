#pragma once
#include "GameObject.hpp"

class Bed : public GameObject {
private:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Bed() {
        if (!texture.loadFromFile("assets/bed.png")) {
            throw std::runtime_error("Failed to load bed.png");
        }
        sprite.setTexture(texture);
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(sprite);
    }

    void setPosition(float x, float y) override {
        sprite.setPosition(x, y);
    }

    std::string getName() const override {
        return "Bed";
    }
};
