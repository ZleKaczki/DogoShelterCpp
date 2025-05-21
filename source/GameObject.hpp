#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual std::string getName() const = 0;
};
