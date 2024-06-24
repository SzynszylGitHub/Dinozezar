#pragma once
#include "Actor.h"

class Bird : public Actor {
public:
    Bird(std::string name, sf::Texture texture, sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f velocity = sf::Vector2f(0, 0))
        : Actor(name, texture, position, velocity) {}

    void updateBehavior();
};
