#include "Actor.h"

void Actor::Update() {
	setPosition(getPosition()+velocity);
}

void Actor::showPosition() { //prototyp przed napisaniem msgbox
	std::cerr << '(' << getPosition().x << " , " << getPosition().y << ')' << '\n';
}

void Actor::setForce(sf::Vector2f force) {
	this->velocity = force;
}

void Actor::setSpeed(float value) {
	this->speed = value;
}

void sth(std::string s) {
	std::cerr << s << '\n';
}

void Actor::move(sf::Event& event,bool show) {
	if (show && (velocity.x != 0 || velocity.y != 0)) showPosition();
	if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
				case sf::Keyboard::W:
					setForce(sf::Vector2f(0.0f, -speed));
					break;
				case sf::Keyboard::S:
					setForce(sf::Vector2f(0.0f, speed));
					break;
				case sf::Keyboard::A:
					setForce(sf::Vector2f(-speed, 0.0f));
					break;
				case sf::Keyboard::D:
					setForce(sf::Vector2f(speed, 0.0f));
					break;
				default:
					break;
			}
		}
	else { 
		setForce(sf::Vector2f(0.f, 0.f)); 
	}
}

void Actor::jump(sf::Event& event,float force) {
	//std::cout << getPosition().y << std::endl;

	if(state == Action::run)
		if ( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
			state = Action::jump;
	
	if (state == Action::jump)
		if (getPosition().y > 200) 
			setForce(sf::Vector2f(0.f, -(speed + force*0.3)));
		else {
			setForce(sf::Vector2f(0.f, 0.f));
			state = Action::fall;
		}
		

	if (state == Action::fall) {
		if (getPosition().y < 400) 
			setForce(sf::Vector2f(0.f, (force * 0.3 + speed)/3));
		else {
			state = Action::run;
			setForce(sf::Vector2f(0.f, 0.f));
			if (getPosition().y > 400)
				setPosition(sf::Vector2f(getPosition().x, 400));
		}
	}
}

void Actor::animate(sf::Time val) {
	static sf::Time last_swap = sf::Time::Zero;
	static bool first = true;

	if(state != Action::fall)
		if (val.asMilliseconds() > last_swap.asMilliseconds()+80 ) // 100 ms = 1 s
		{
			//std::cout << last_swap.asSeconds() << std::endl;
			last_swap = val;
			if (first) {
				texture.setTexture(SecTxt);
				first = false;
			}
			else {
				texture.setTexture(IMG);
				first = true;
			}
		}

}
void Actor::setAnimetionTXT(sf::Texture& p1, sf::Texture& p2) {
	IMG = p1;
	SecTxt = p2;
}
