#include "Window.h"

Window::Window(std::string name)
{
    setBackground("asset/background.png");
    handle.create(sf::VideoMode(800, 600), name, sf::Style::Close);
    handle.setFramerateLimit(60);
}
Window::Window(std::string name, int width, int height) {
    setBackground("asset/background.png");
    handle.create(sf::VideoMode(width, height), name, sf::Style::Close);
    handle.setFramerateLimit(60);
}

Window::Window(std::string name, bool fullscreen) {
    if (!fullscreen) {
        Window("Default");
        return;
    }
    handle.create(sf::VideoMode::getFullscreenModes()[0], name, sf::Style::Fullscreen);
}

bool Window::isOpen()
{
    return handle.isOpen();
}

void Window::Render() {
    handle.clear();
    handle.draw(background);
    handle.display();
}

void Window::Render(Actor& player, std::vector<Actor*>& Characters)
{
    handle.clear();
    handle.draw(background);

    for (auto& Pawn : Characters) {
        Pawn->Update();
        Pawn->choiceDraw(handle);
    }

    player.Update();
    player.choiceDraw(handle);
}

void Window::display() {
    handle.display();
}

sf::RenderWindow& Window::getHandle() {
    return handle;
}

bool Window::pollEvent(sf::Event& event)
{
    if (!handle.isOpen()) return false;
    handle.pollEvent(event);
    return true;
}

bool Window::setBackground(std::string adress) {
    if (!backgroundTexture.loadFromFile(adress)) {
        std::cerr << "Error loading " << adress << " image" << std::endl;
        return false;
    }
    background.setTexture(backgroundTexture);
    return true;
}

void Window::close() {
    handle.close();
}
