#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Entity{
public:
	Entity();
	Entity(std::string name, sf::Texture texture,
		sf::Vector2f position = sf::Vector2f(0, 0),
		sf::Vector2f velocity = sf::Vector2f(0, 0)
	);
	std::string getName();
	
	bool setTexture(std::string adress);
	void setTexture(sf::Texture texture);
	sf::Vector2f getSize();

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f vel);
	
	bool getHit(Entity& entity);
	sf::FloatRect getHitbox();

	void draw(sf::RenderWindow& handle);
	void drawRS(sf::RenderWindow& handle);
	
	void choiceDraw(sf::RenderWindow& handle);
	
	void hitbox_visibility(bool state);
	void corect_hitbox(sf::Vector2f Size, sf::Vector2f corect = sf::Vector2f(2, 2),bool is = false);
	void setShapePawn(sf::Color color,bool active = false);
	void setShapePawn(sf::Color color,sf::Vector2f Size = sf::Vector2f(50.0f, 50.0f),bool active = false);
	
	void move(sf::Vector2f velocity);
protected:
	sf::Vector2f velocity;
	sf::Sprite texture;
	sf::Texture IMG;
private:
	std::string name;
	sf::Vector2f position;
	sf::Vector2f pos_delay = sf::Vector2f(5,5);
	sf::RectangleShape rectangle;
	bool isAction;
	bool isShape;
};