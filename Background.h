#pragma once
#include "Actor.h"

class Background : public Actor {
public:
    Background(std::string name, sf::Texture texture, sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f velocity = sf::Vector2f(0, 0))
        : Actor(name, texture, position, velocity) {}

    void updateBehavior();
};
