#pragma once
#include <windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "SFML\Network.hpp"

class Network
{
private:
	std::string server;
	sf::Http http;
	sf::Http::Request request;
	sf::Http::Response response = http.sendRequest(request);
	std::string roomId;
	std::string color;
public:
	Network() { 	};
	void setHost(std::string _server) { server = _server; http.setHost(_server); }
	bool connectTest();
	bool updateAct(std::string act);
	std::string getAct();
	std::string getColor() { return color; };
	std::string getRoomId() { return roomId; };
	bool delRoom();
	bool create_or_join_room(std::string _roomId);
	int commnd_index = 0;

};

