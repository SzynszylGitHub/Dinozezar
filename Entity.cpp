#include "Entity.h"


Entity::Entity() {
	IMG.loadFromFile("asset/blank.png");
	texture.setTexture(IMG);
	velocity = sf::Vector2f(0, 0);
	position = sf::Vector2f(0, 0);
	isAction = false;
	isShape = false;
	name = "Empty Pawn";
	this->setShapePawn(sf::Color::Red, true);
}

Entity::Entity(std::string name, sf::Texture texture, sf::Vector2f position, sf::Vector2f velocity) {
	this->name = name;
	IMG = texture;
	this->texture.setTexture(IMG);
	this->position = position;
	this->texture.setPosition(position);
	this->velocity = velocity;
	this->setShapePawn(sf::Color::Green,
		sf::Vector2f(IMG.getSize().x - pos_delay.x,IMG.getSize().y - pos_delay.y), 
		true
	);
	this->isShape = false;
}

std::string Entity::getName() {
	return name;
}

bool Entity::setTexture(std::string adress) {
	if (!IMG.loadFromFile(adress)) return false;
	this->texture.setTexture(IMG);
	return true;
}

void Entity::setTexture(sf::Texture texture) {
	IMG = texture;
	this->texture.setTexture(IMG);
}
sf::Vector2f Entity::getSize() {
	return sf::Vector2f(IMG.getSize().x, IMG.getSize().y);
}


void Entity::setPosition(sf::Vector2f position) {
	this->position = position;
	texture.setPosition(position);
	rectangle.setPosition(position + pos_delay);
}

sf::Vector2f Entity::getPosition() {
	return position;
}

sf::Vector2f Entity::getVelocity() {
	return velocity;
}

void Entity::setVelocity(sf::Vector2f vel) {
	velocity = vel;
}



bool Entity::getHit(Entity& entity) {
	if (this->rectangle.getGlobalBounds().intersects(entity.getHitbox())) {
		return true;
	}
	return false;
}

sf::FloatRect Entity::getHitbox() {
	return rectangle.getGlobalBounds();
}


void Entity::draw(sf::RenderWindow& handle) {
	 handle.draw(texture);
}

void Entity::drawRS(sf::RenderWindow& handle) {
	handle.draw(rectangle);
}
void Entity::choiceDraw(sf::RenderWindow& handle) {
	if (!isShape) draw(handle);
	else drawRS(handle);
}

void Entity::hitbox_visibility(bool state) {
	isShape = state;
}

void Entity::corect_hitbox(sf::Vector2f Size,sf::Vector2f corect,bool is) {
	if (is) pos_delay = corect;
	else pos_delay = sf::Vector2f(Size.x / 2, Size.y / 2);
	sf::Vector2f xSize = sf::Vector2f(IMG.getSize().x - Size.x,IMG.getSize().y - Size.y);
	rectangle.setSize(xSize);
}

void Entity::setShapePawn(sf::Color color,bool active) {
	rectangle.setFillColor(color);
	rectangle.setSize(sf::Vector2f(50.0f,50.0f));
	rectangle.setPosition(position);
	isShape = active;
}

void Entity::setShapePawn(sf::Color color, sf::Vector2f Size, bool active){
	rectangle.setFillColor(color);
	rectangle.setSize(Size);
	rectangle.setPosition(position);
	isShape = active;
}

void Entity::move(sf::Vector2f velocity) {
	texture.move(velocity);
	rectangle.move(velocity);
}