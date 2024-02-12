#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Button
{
protected:
	sf::Texture texture;
	sf::Sprite body;
	std::string name;

public:
	Button();
	Button(std::string);
	Button(sf::Vector2f);
	Button(sf::Vector2f, std::string);
	Button(Button*);
	Button operator=(const Button&);
	void setPosition(sf::Vector2f);
	void setName(std::string);
	void setTexture(std::string);
	bool isClicked(sf::Event&);
	sf::Sprite getBody() const { return body; }
	std::string getName() { return name; }
};