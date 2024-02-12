#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>



class OutputLog
{
	//Player: 1, Action: Soldier (4, 6) -> (4, 5)
public:
	OutputLog() {};
	~OutputLog() {};
	std::vector<std::string> logArray;
	void writeLog(std::string, std::string, int, int, int, int);
	void writeWinner(std::string);
	void outputLogFile();

};

