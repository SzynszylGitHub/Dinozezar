#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Actor.h"

class Window
{
public:
    Window(std::string name = "Dino Zezar");
    Window(std::string name, int width, int height);
    Window(std::string name, bool fullscreen);
    bool isOpen();
    void Render(Actor& player, std::vector<Actor*>& Characters);
    void Render();
    void display();
    sf::RenderWindow& getHandle();
    bool pollEvent(sf::Event& event);
    bool setBackground(std::string adress);
    void close();

private:
    sf::RenderWindow handle;
    sf::Texture backgroundTexture;
    sf::Sprite background;
};
