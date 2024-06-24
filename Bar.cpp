#include "Bar.h"

Bar::Bar(std::string title,sf::Font& font,sf::Vector2f position,sf::Vector2f size)
	:_text(title,font){
	_title = title;

	
	
	_background.setPosition(position);
	_background.setFillColor(sf::Color::Cyan);
	_background.setSize(size);

	_font = font;
	_text.setPosition(_background.getPosition());
	_text.setFillColor(sf::Color::Black);
	_text.setFont(_font);
	
}

void Bar::add_sth(std::string sth) {
	_title += sth;
	_text.setString(_title);
}

void Bar::setString(std::string sth) {
	_title = sth;
	_text.setString(_title);
}

void Bar::center() {

	sf::Vector2f size = _background.getSize();
	recorect_position = _background.getPosition();
	
	recorect_position.x += size.x/2 - (_title.size()*(_text.getCharacterSize()/(_text.getCharacterSize()/10 + 1)));
	recorect_position.y += size.y/2 - _text.getCharacterSize();
	_text.setPosition(recorect_position);

	//printf("%d\n", _text.getCharacterSize());
}

void Bar::draw(sf::RenderWindow& handle) {
	handle.draw(_background);
	handle.draw(_text);
}

void Bar::setTitlePosition(sf::Vector2f position) {
	recorect_position = position; 
}

void Bar::setFont(sf::Font& font) { 
	_font = font; 
}

void Bar::reSizeCharacter(float size) { 
	_text.setCharacterSize(size);
}

std::string Bar::getTitle() { 
	return _title; 
}

void Bar::clear() { 
	_title = ""; 
}

void Bar::reSizeRectangle(sf::Vector2f size) {
	_background.setSize(size);
}

void Bar::setPosition(sf::Vector2f position) {
	_background.setPosition(position);
	_text.setPosition(position + recorect_position);
}


void Bar::setColorRectangle(sf::Color color) {
	_background.setFillColor(color);
}

void Bar::setColorCharacter(sf::Color color) {
	_text.setFillColor(color);
}

sf::Vector2f Bar::getRectangleSize() {
	return _background.getSize();
}
