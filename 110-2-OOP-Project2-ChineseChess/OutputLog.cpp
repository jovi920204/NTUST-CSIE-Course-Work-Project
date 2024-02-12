#include "OutputLog.h"

void OutputLog::writeLog(std::string color, std::string chess, int x1, int y1, int x2, int y2)
{
	// format
	//Player: 1, Action: Soldier (4, 6) -> (4, 5)
	std::string log = "Player: ";
	if (color == "red") log += "1, Action: ";
	else log += "2, Action: ";
	if (chess == "king") {
		log += "General";
	}
	else if (chess == "advisor") {
		log += "Advisor";
	}
	else if (chess == "elephant") {
		log += "Elephant";
	}
	else if (chess == "horse") {
		log += "Horse";
	}
	else if (chess == "chariot") {
		log += "Chariot";
	}
	else if (chess == "cannon") {
		log += "Cannon";
	}
	else if (chess == "soldier") {
		log += "Soldier";
	}
	
	log +=" (" + std::to_string(y1) + ", " + std::to_string(x1) + ") -> (" + std::to_string(y2) + ", " + std::to_string(x2) + ")";
	logArray.push_back(log);
}

void OutputLog::writeWinner(std::string winner)
{
	std::string log = "";
	if (winner == "red") {
		log = "Red Win";
	}
	else {
		log = "Black Win";
	}
	logArray.push_back(log);
}

void OutputLog::outputLogFile()
{	std::time_t now_time;
	now_time = time(NULL);
	std::string logFilePath = "replaylog/log_" + std::to_string(now_time) + ".txt";
	std::ofstream ofs(logFilePath);
	for (int i = 0; i < logArray.size(); i++) {
		ofs << logArray[i]<< "\n";
	}
	ofs.close();
}
