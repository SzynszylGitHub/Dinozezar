#pragma once
#include "Entity.h"

enum class Action{
	run,
	jump,
	fall
};

class Actor : public Entity
{
public:
	Actor() : Entity() {}
	Actor(std::string name,sf::Texture texture,
		sf::Vector2f position = sf::Vector2f(0, 0),
		sf::Vector2f velocity = sf::Vector2f(0, 0))
		: Entity(name,texture,position,velocity) {}

	void Update();
	void setSpeed(float value);
	void setForce(sf::Vector2f force);
	void showPosition();
	void move(sf::Event& event,bool show = false);
	void jump(sf::Event& event,float force);
	void animate(sf::Time);
	void setAnimetionTXT(sf::Texture&, sf::Texture&);

private: 
	float speed = 4.f;
	bool isAction = false;
	Action state = Action::run;
	sf::Texture SecTxt;
};

