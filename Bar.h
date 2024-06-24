#pragma once
#include "SFML/Graphics.hpp"


class Bar
{
public:
	Bar(std::string,sf::Font&,sf::Vector2f position = sf::Vector2f(0,0),sf::Vector2f size = sf::Vector2f(800,200));
	void setString(std::string);
	void add_sth(std::string sth);
	std::string getTitle();
	void clear();

	void reSizeCharacter(float);
	void setFont(sf::Font&);
	void center();
	void setTitlePosition(sf::Vector2f);

	void reSizeRectangle(sf::Vector2f);
	void setPosition(sf::Vector2f);
	void setColorRectangle(sf::Color);
	void setColorCharacter(sf::Color);

	sf::Vector2f getRectangleSize();

	void draw(sf::RenderWindow&);
private:
	sf::Vector2f recorect_position;
	std::string _title;
	sf::Font _font;
	sf::Text _text;
	sf::RectangleShape _background;
};

