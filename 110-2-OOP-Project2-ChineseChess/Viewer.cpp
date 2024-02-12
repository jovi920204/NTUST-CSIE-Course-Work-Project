#include "Viewer.h"

Viewer::Viewer()
{
	this->window = nullptr;
	this->boardBackground = nullptr;
	this->title = nullptr;
}

Viewer::~Viewer()
{
	if (this->window != nullptr)
		delete this->window;
	if (this->boardBackground != nullptr)
		delete this->boardBackground;
	if (this->title != nullptr)
		delete this->title;
}

void Viewer::initMainPage()
{
	if (this->window != nullptr)
		delete this->window;
	sf::VideoMode videoMode(480, 650);
	this->window = new sf::RenderWindow(videoMode, "Main menu", sf::Style::Titlebar | sf::Style::Close);

	this->titleTexture.loadFromFile("image/title.png");
	this->title = new sf::Sprite();
	this->title->setTexture(titleTexture);
	this->title->setPosition(90, 30);

	this->startButton.setName("start_button");
	this->startButton.setPosition({ 117,150 });
	this->startButton.setTexture("image/start_button.png");

	this->loadButton.setName("load_button");
	this->loadButton.setPosition({ 117,250 });
	this->loadButton.setTexture("image/load_button.png");

	this->onlineButton.setName("online_button");
	this->onlineButton.setPosition({ 117,350 });
	this->onlineButton.setTexture("image/online_button.png");

	this->exitButton.setName("exit_button");
	this->exitButton.setPosition({ 117,450 });
	this->exitButton.setTexture("image/exit_button.png");
}

void Viewer::initGamePage()
{
	if (this->window != nullptr)
		delete this->window;
	sf::VideoMode videoMode(1500, 875);
	this->window = new sf::RenderWindow(videoMode, "ChineseChess", sf::Style::Titlebar | sf::Style::Close);
	// Board init
	this->boardTexture.loadFromFile("image/board.jpg");
	this->boardBackground = new sf::Sprite();
	this->boardBackground->setTexture(boardTexture);
	this->boardBackground->setPosition(20, 20);

	this->surrenderButton.setName("surrender_button");
	this->surrenderButton.setPosition({ 1400,775 });
	this->surrenderButton.setTexture("image/surrender.png");
	this->start_time = time(NULL);
}
void Viewer::initOnlinePage()
{
	if (this->window != nullptr)
		delete this->window;
	sf::VideoMode videoMode(1500, 875);
	this->window = new sf::RenderWindow(videoMode, "ChineseChess", sf::Style::Titlebar | sf::Style::Close);
	// Board init
	this->boardTexture.loadFromFile("image/board.jpg");
	this->boardBackground = new sf::Sprite();
	this->boardBackground->setTexture(boardTexture);
	this->boardBackground->setPosition(20, 20);

	//display hint
	window->clear(sf::Color::White);
	sf::Texture hintTexture;
	hintTexture.loadFromFile("image/hint.png");
	sf::Sprite hintSprite(hintTexture);
	window->draw(hintSprite);
	window->display();

	this->onlineGame.setHost("http://chinesechess.azurewebsites.net/");
	std::string roomId;
	std::cout << "Please input room ID to join or craete room\n";
	std::cin >> roomId;
	while (!onlineGame.create_or_join_room(roomId)) {
		std::cout << "Room ID unavailable\n";
		std::cout << "Please input room ID to join or craete room\n";
		std::cin >> roomId;
	}
	this->last_update_time = time(NULL);
}
void Viewer::initReplayPage()
{
	replay.selectFile();
	replay.readFile();
	replay.setMoveIndex(0);
	initGamePage();
	this->nextStepButton.setName("next_step_button");
	this->nextStepButton.setPosition({ 1280,80 });
	this->nextStepButton.setTexture("image/next_step_button.png");
}

int Viewer::updateMainPage(sf::Event ev)
{
	int flowControl = 0;
	switch (ev.type)
	{
	case sf::Event::Closed:
		window->close();
		break;
	case sf::Event::MouseButtonPressed:
		if (startButton.isClicked(ev))
		{
			flowControl = 1;	// enter game page
			return flowControl;
			// initGamePage();
		}
		else if (exitButton.isClicked(ev))
		{
			window->close();
		}
		else if (loadButton.isClicked(ev))
		{
			flowControl = 2;
			return flowControl;
		}
		else if (onlineButton.isClicked(ev))
		{
			flowControl = 3;
			return flowControl;
		}
		break;
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Escape)
			window->close();
		break;
	}
	return flowControl;
}

int Viewer::updateGamePage(sf::Event ev, Board* board)
{
	int flowControl = 1;
	Chess* clickChess = nullptr;
	
	switch (ev.type)
	{
	case sf::Event::Closed:
		board->outputLog.outputLogFile();
		window->close();
		break;
	case sf::Event::MouseButtonPressed:
	{

		// click Board
		clickChess = board->clickBoard(ev, window);
		if (surrenderButton.isClicked(ev)) {
			std::string winColor;
			winColor = board->getRoundCount() % 2 != 0 ? "red" : "black";
			board->setWinner(winColor);
		}
		if (clickChess != nullptr)
		{
			std::cout << clickChess->getName() << ' ' << clickChess->getColor() << "\n";

			// Function which judge is CheckMate or not
			std::string checkmate = board->getCheckmate();
			if (checkmate != "") { // if checkMate confirmed, send the message to player.
				std::string msg;
				if (checkmate == "red") msg = "red checkmate";
				if (checkmate == "black") msg = "black checkmate";
				MessageBoxA(NULL, msg.c_str(), "Message", MB_OKCANCEL | MB_ICONEXCLAMATION);
				board->setCheckmate("");
			}
		}
		// Function which judge is over or not
		std::string winner = board->getWinner();
		if (winner != "") { // if overed, show the result, and player can choice play again or not.
			std::string msg;
			if (winner == "red") msg = "red win";
			if (winner == "black") msg = "black win";
			if (winner == "tie") msg = "Tie";
			MessageBoxA(NULL, msg.c_str(), "Message", MB_OK);

			int result = MessageBoxA(NULL, "play again?", "Message", MB_OKCANCEL);
			(*board).resetBoard();
			this->start_time = time(NULL);
			if (result == 2) // back to main menu
			{
				flowControl = 0;
				return flowControl;
			}
		}
		break;
	}
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Escape)
			window->close();
		if (ev.key.code == sf::Keyboard::Delete)
		{
			Point index = board->getChosenChessIndex();
			if (index.x != -1 && index.y != -1)
			{
				board->removeChess(index);
				board->setChosenChessIndex({ -1,-1 });
			}
		}
		break;
	}
	return flowControl;
}
int Viewer::updateGamePage(Board* board) {
	int flowControl = 1;

	std::string winner = board->getWinner();
	if (winner != "") { // if overed, show the result, and player can choice play again or not.
		std::string msg;
		if (winner == "red") msg = "red win";
		if (winner == "black") msg = "black win";
		if (winner == "tie") msg = "Tie";
		MessageBoxA(NULL, msg.c_str(), "Message", MB_OK);

		int result = MessageBoxA(NULL, "play again?", "Message", MB_OKCANCEL);
		(*board).resetBoard();
		this->start_time = time(NULL);
		if (result == 2) // back to main menu
		{
			flowControl = 0;
			return flowControl;
		}
	}
	return flowControl;
}
int Viewer::updateReplayPage(sf::Event ev, Board* board)
{
	int flowControl = 2;
	switch (ev.type)
	{
	case sf::Event::Closed:
		window->close();
		break;
	case sf::Event::MouseButtonPressed:
		// std::cout << ev.mouseButton.x << ' ' << ev.mouseButton.y << '\n';
		if (nextStepButton.isClicked(ev))
		{
			std::string move = replay.getCurrent();
			sf::Event replayEV;
			replayEV.type = sf::Event::MouseButtonPressed;
			replayEV.mouseButton.x = 54 + (move[1] - '0') * 87.5 + 37.5;
			replayEV.mouseButton.y = 50 + (move[3] - '0') * 85.5 + 37.5;
			board->clickBoard(replayEV, window);
			replayEV.mouseButton.x = 54 + (move[6] - '0') * 87.5 + 37.5;
			replayEV.mouseButton.y = 50 + (move[8] - '0') * 85.5 + 37.5;
			board->clickBoard(replayEV, window);
			
			replay++;
			if (move == replay.getBackMove())
			{
				if (replay.getStatus() == -1) {
					std::string finish = "the replay log is finish¡AContinue?";
					//MessageBoxA(NULL, finish.c_str(), "Message", MB_OK);

					int result = MessageBoxA(NULL, finish.c_str(), "Message", MB_OKCANCEL);
					if (result == 1) //Continue
					{
						(*board).setCheckmate("");
						replay.reset();
						flowControl = 1;
						return flowControl;
					}

					
					if (result == 2) // back to main menu
					{
						replay.reset();
						flowControl = 0;
						(*board).resetBoard();
						return flowControl;
					}
					
					
				}
				else {
					std::string winner = (replay.getStatus() == 0 ? "red win" : "black win");
					MessageBoxA(NULL, winner.c_str(), "Message", MB_OK);
					(*board).resetBoard();
					replay.reset();
				}

				flowControl = 0;
				return flowControl;
			}
		}
		break;
	}
	return flowControl;
}
int Viewer::updateOnlinePage(sf::Event ev, Board* board,bool is_from_user) {
	int flowControl = 3;
	Chess* clickChess = nullptr;

	switch (ev.type)
	{
	case sf::Event::Closed:
		onlineGame.delRoom();
		window->close();
		break;
	case sf::Event::MouseButtonPressed:
	{
		std::string thitRoundColor;
		thitRoundColor = board->getRoundCount() % 2 == 0 ? "red" : "black";
		if (is_from_user == false || thitRoundColor == onlineGame.getColor()) {

			if (is_from_user) {
				//online game
				std::string act;
				act = std::to_string(ev.mouseButton.x) + "," + std::to_string(ev.mouseButton.y);
				onlineGame.updateAct(act);
			}
			// click Board

			clickChess = board->clickBoard(ev, window);
			if (surrenderButton.isClicked(ev)) {
				std::string winColor;
				winColor = board->getRoundCount() % 2 != 0 ? "red" : "black";
				board->setWinner(winColor);
			}
			if (clickChess != nullptr)
			{
				std::cout << clickChess->getName() << ' ' << clickChess->getColor() << "\n";

				// Function which judge is CheckMate or not
				std::string checkmate = board->getCheckmate();
				if (checkmate != "") { // if checkMate confirmed, send the message to player.
					std::string msg;
					if (checkmate == "red") msg = "red checkmate";
					if (checkmate == "black") msg = "black checkmate";
					MessageBoxA(NULL, msg.c_str(), "Message", MB_OK);
					board->setCheckmate("");
				}
			}
			// Function which judge is over or not
			std::string winner = board->getWinner();
			if (winner != "") { // if overed, show the result, and player can choice play again or not.
				std::string msg;
				if (winner == "red") msg = "red win";
				if (winner == "black") msg = "black win";
				if (winner == "tie") msg = "Tie";
				MessageBoxA(NULL, msg.c_str(), "Message", MB_OK);

				//int result = MessageBoxA(NULL, "END", "Message", MB_OK);
				(*board).resetBoard();
				flowControl = 0;
				return flowControl;

			}

		}
		return flowControl;
		break;
	}
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Escape)
			window->close();
		if (ev.key.code == sf::Keyboard::Delete)
		{
			Point index = board->getChosenChessIndex();
			if (index.x != -1 && index.y != -1)
			{
				board->removeChess(index);
				board->setChosenChessIndex({ -1,-1 });
			}
		}
		break;
	}
	return flowControl;
}
int Viewer::updateOnlinePage(Board* board) {
	now_time = time(NULL);
	if (now_time - last_update_time >= update_interval) {
		std::string act = onlineGame.getAct();
		//std::cout << act << ','<< onlineGame.commnd_index<<'\n';
		last_update_time = time(NULL);
		if (act != "OUT_OF_RANGE" && act != "new") {
			sf::Event onlineEV;
			onlineEV.type = sf::Event::MouseButtonPressed;
			onlineEV.mouseButton.x = std::stoi(act.substr(0, 4));
			onlineEV.mouseButton.y = std::stoi(act.substr(5, 4));
			return updateOnlinePage(onlineEV, board,false);

		}
	}
	return 3;
}
void Viewer::showMainPage()
{
	window->clear(sf::Color::White);
	window->draw(*title);
	window->draw(startButton.getBody());
	window->draw(loadButton.getBody());
	window->draw(onlineButton.getBody());
	window->draw(exitButton.getBody());
	window->display();
}

void Viewer::showGamePage(Board* board)
{
	this->now_time = time(NULL);
	if (timeLimit - (now_time - start_time) <= 0) {
		board->setWinner("tie");
	}
	window->clear(sf::Color::White);
	window->draw(*this->boardBackground);
	// draw chess and the position that chess can move to
	for (auto& v : board->getBoard()) {
		for (auto& c : v) {
			sf::Sprite sp = c->getBody();
			if (c->canMove_flag) {
				if (c->getName() == "empty") {
					sf::CircleShape shape(37.f);
					shape.setPosition(sp.getPosition());
					shape.setFillColor(sf::Color::Color(255, 0, 0, 120));

					window->draw(shape);
					continue;
				}
				else {
					sp.setColor(sf::Color::Red);
					window->draw(sp);
				}
			}
			if (c->getName() != "empty")
				window->draw(sp);
		}
	}

	// display dead chesses and 
	std::vector<std::string> removedChesses = board->getRemovedChesses();
	for (int i = 0; i < removedChesses.size(); i++) {
		std::string path = removedChesses[i];
		sf::Vector2f position = sf::Vector2f(850 + (i / 8) * 100, 75 + (i % 8) * 100);
		sf::Texture texture;
		texture.loadFromFile(path);
		sf::Sprite sp;
		sp.setTexture(texture);
		sp.setPosition(position);
		window->draw(sp);
	}

	// display which side should move
	std::string thitRoundColor;
	thitRoundColor = board->getRoundCount() % 2 == 0 ? "red" : "black";
	sf::Font font;
	font.loadFromFile("font/arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Current Player : " + thitRoundColor);
	sf::Vector2f position = sf::Vector2f(850, 10);
	text.setPosition(position);
	text.setCharacterSize(50); // in pixels, not points!
	text.setFillColor(sf::Color::Black);
	window->draw(text);

	//display timer
	std::string time = std::to_string(timeLimit - (now_time - start_time));
	font.loadFromFile("font/arial.ttf");
	text.setFont(font);
	text.setString(time);
	position = sf::Vector2f(1350, 785);
	text.setPosition(position);
	text.setCharacterSize(50); // in pixels, not points!
	text.setFillColor(sf::Color::Black);
	window->draw(text);

	window->draw(surrenderButton.getBody());
	window->display();
}

void Viewer::showReplayPage(Board* board)
{
	window->clear(sf::Color::White);
	window->draw(nextStepButton.getBody());

	window->draw(*this->boardBackground);
	for (auto& v : board->getBoard())
	{
		for (auto& c : v)
		{
			if (c->getName() != "empty")
				window->draw(c->getBody());
		}
	}

	// display dead chesses and 
	std::vector<std::string> removedChesses = board->getRemovedChesses();
	for (int i = 0; i < removedChesses.size(); i++) {
		std::string path = removedChesses[i];
		sf::Vector2f position = sf::Vector2f(850 + (i / 8) * 100, 75 + (i % 8) * 100);
		sf::Texture texture;
		texture.loadFromFile(path);
		sf::Sprite sp;
		sp.setTexture(texture);
		sp.setPosition(position);
		window->draw(sp);
	}

	// display which side should move
	std::string thitRoundColor;
	thitRoundColor = board->getRoundCount() % 2 == 0 ? "red" : "black";
	sf::Font font;
	font.loadFromFile("font/arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Current Player : " + thitRoundColor);
	sf::Vector2f position = sf::Vector2f(850, 10);
	text.setPosition(position);
	text.setCharacterSize(50); // in pixels, not points!
	text.setFillColor(sf::Color::Black);
	window->draw(text);
	window->display();
}
void Viewer::showOnlinePage(Board* board)
{
	
	window->clear(sf::Color::White);
	window->draw(*this->boardBackground);
	// draw chess and the position that chess can move to
	for (auto& v : board->getBoard()) {
		for (auto& c : v) {
			sf::Sprite sp = c->getBody();
			if (c->canMove_flag) {
				if (c->getName() == "empty") {
					sf::CircleShape shape(37.f);
					shape.setPosition(sp.getPosition());
					shape.setFillColor(sf::Color::Color(255, 0, 0, 120));

					window->draw(shape);
					continue;
				}
				else {
					sp.setColor(sf::Color::Red);
					window->draw(sp);
				}
			}
			if (c->getName() != "empty")
				window->draw(sp);
		}
	}

	// display dead chesses and 
	std::vector<std::string> removedChesses = board->getRemovedChesses();
	for (int i = 0; i < removedChesses.size(); i++) {
		std::string path = removedChesses[i];
		sf::Vector2f position = sf::Vector2f(850 + (i / 7) * 100, 125 + (i % 7) * 100);
		sf::Texture texture;
		texture.loadFromFile(path);
		sf::Sprite sp;
		sp.setTexture(texture);
		sp.setPosition(position);
		window->draw(sp);
	}

	// display which side should move
	std::string thitRoundColor;
	thitRoundColor = board->getRoundCount() % 2 == 0 ? "red" : "black";
	sf::Font font;
	font.loadFromFile("font/arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Current Player : " + thitRoundColor);
	sf::Vector2f position = sf::Vector2f(850, 10);
	text.setPosition(position);
	text.setCharacterSize(50); // in pixels, not points!
	text.setFillColor(sf::Color::Black);
	window->draw(text);

	text.setString("Your color        : " + onlineGame.getColor());
	position = sf::Vector2f(850, 60);
	text.setPosition(position);
	window->draw(text);

	text.setCharacterSize(25);
	text.setString("Room ID : " + onlineGame.getRoomId());
	position = sf::Vector2f(1200, 840);
	text.setPosition(position);
	window->draw(text);

	//window->draw(surrenderButton.getBody());
	window->display();
}