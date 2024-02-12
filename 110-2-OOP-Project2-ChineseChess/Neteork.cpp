#include "Network.h"

bool Network::create_or_join_room(std::string _roomId) {
	this->roomId = _roomId;
	
	// encode the parameters in the request body
	std::ostringstream stream;
	stream << "?roomId=" << roomId ;
	request = sf::Http::Request("/create_room"+ stream.str(), sf::Http::Request::Get);

	 response = http.sendRequest(request);

	 if (response.getBody() == "red") {
		 color = "red";
		 return true;
	 }
	 else if(response.getBody() == "black") 
	 {
		 color = "black";
		 return true;
	 }
	 else {
		 return false;
	 }

}
bool Network::updateAct(std::string act) {
	

	// encode the parameters in the request body
	std::ostringstream stream;
	stream << "?roomId=" << roomId << "&act="<<act<< "&color="<<color;
	//std::cout << stream.str()<<std::endl;
	request = sf::Http::Request("/update_act"+ stream.str(), sf::Http::Request::Get);

	response = http.sendRequest(request);

	// check the status
	return (response.getStatus() == sf::Http::Response::Ok);


}
std::string Network::getAct() {

	// encode the parameters in the request body
	std::ostringstream stream;
	stream << "?roomId=" << roomId << "&color=" << color << "&index="<<commnd_index;
	request = sf::Http::Request("/get_act"+ stream.str(), sf::Http::Request::Get);

	response = http.sendRequest(request);
	if (response.getBody() != "OUT_OF_RANGE") {
		commnd_index += 1;
	}
	// check the status
	return response.getBody();
}
bool Network::delRoom() {
	

	// encode the parameters in the request body
	std::ostringstream stream;
	stream << "?roomId=" << roomId;
	request = sf::Http::Request("/del_room"+ stream.str(), sf::Http::Request::Get);

	response = http.sendRequest(request);

	// check the status
	return (response.getStatus() == sf::Http::Response::Ok);
}
bool Network::connectTest() {
	request = sf::Http::Request("/connect_test", sf::Http::Request::Get);

	response = http.sendRequest(request);

	// check the status
	return response.getStatus() == sf::Http::Response::Ok;

}