#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

#include "Button.h"

class Chess : virtual public Button {
protected:
	std::string color;
	std::string logName = "";
public:
	Chess() {};
	~Chess() {};
	
	std::string getColor() { return color; };
	bool getMoveFlag() { return canMove_flag; };
	virtual bool canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard) { return 0; }
	bool canMove_flag = false;
};

class Empty : public Chess {
public:
	Empty(sf::Vector2f position) : Button(position, "empty") {
		std::string path = "image/empty.png";
		this->setTexture(path);
	};
};

class King : public Chess {
public:
	King(sf::Vector2f position, std::string color) : Button(position, "king") {
		this->color = color;
		std::string path = "image/" + color + "/" + name + ".png";
		this->setTexture(path);
	};
	~King() {};

	bool canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard);
};

class Advisor : public Chess {
public:
	Advisor(sf::Vector2f position, std::string color) : Button(position, "advisor") {
		this->color = color;
		std::string path = "image/" + color + "/" + name + ".png";
		this->setTexture(path);
	};
	~Advisor() {};

	bool canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard);
};

class Elephant : public Chess {
public:
	Elephant(sf::Vector2f position, std::string color) : Button(position, "elephant") {
		this->color = color;
		std::string path = "image/" + color + "/" + name + ".png";
		this->setTexture(path);
	};
	~Elephant() {};

	bool canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard);
};

class Horse : public Chess {
public:
	Horse(sf::Vector2f position, std::string color) : Button(position, "horse") {
		this->color = color;
		std::string path = "image/" + color + "/" + name + ".png";
		this->setTexture(path);
	};
	~Horse() {};

	bool canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard);
};

class Chariot : public Chess {
public:
	Chariot(sf::Vector2f position, std::string color) : Button(position, "chariot") {
		this->color = color;
		std::string path = "image/" + color + "/" + name + ".png";
		this->setTexture(path);
	};
	~Chariot() {};

	bool canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard);
};

class Cannon : public Chess {
public:
	Cannon(sf::Vector2f position, std::string color) : Button(position, "cannon") {
		this->color = color;
		std::string path = "image/" + color + "/" + name + ".png";
		this->setTexture(path);
	};
	~Cannon() {};

	bool canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard);
};

class Soldier : public Chess {
public:
	Soldier(sf::Vector2f position, std::string color) : Button(position, "soldier") {
		this->color = color;
		std::string path = "image/" + color + "/" + name + ".png";
		this->setTexture(path);
	};
	~Soldier() {};

	bool canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard);
};
/*
帥 General
仕 Advisor
相 Elephant
傌 Horse
俥 Chariot
炮 Cannon
兵 Soldier
*/