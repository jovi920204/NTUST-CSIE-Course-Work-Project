#include "Button.h"

Button::Button()
{
	this->name = "";
	this->body = sf::Sprite();
	this->texture = sf::Texture();
}

Button::Button(sf::Vector2f position)
{
	body.setPosition(position.x, position.y);
}

Button::Button(std::string name)
{
	this->name = name;
}

Button::Button(sf::Vector2f position, std::string name)
{
	this->name = name;
	body.setPosition(position.x, position.y);
}

Button::Button(Button* target)
{
	this->texture = target->texture;
	this->body = target->body;
	this->name = target->name;
}

Button Button::operator=(const Button& target)
{
	return Button(target);
}

void Button::setPosition(sf::Vector2f position)
{
	body.setPosition(position.x, position.y);
}

void Button::setName(std::string name)
{
	this->name = name;
}

void Button::setTexture(std::string path)
{
	texture.loadFromFile(path);
	body.setTexture(texture);
}

bool Button::isClicked(sf::Event& ev)
{
	if (ev.type != sf::Event::MouseButtonPressed)
		return false;

	sf::Vector2f clickPos = sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y);
	sf::Vector2f btnPos = body.getPosition();
	sf::Vector2f btnEnd = btnPos + sf::Vector2f(texture.getSize().x, texture.getSize().y);

	if (clickPos.x<btnPos.x || clickPos.x>btnEnd.x)
		return false;
	if (clickPos.y<btnPos.y || clickPos.y>btnEnd.y)
		return false;
	return true;
}