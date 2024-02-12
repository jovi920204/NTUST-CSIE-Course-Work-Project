// Name: ±i∫Õ≈Ô
// Date: March, 27 , 2022  
// Last Update: March, 27 , 2022  
// Problem statement: Observation Diary
#pragma once
#include "Diary.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Creature {
private:
	string name;
	int startDayIndex;
	string currentBody;
	map<string, int> mp;
public:
	Creature(string _name);
	Creature(string _name, Creature c);
	Creature& operator[](string body);
	Creature& operator=(int value);
	Creature& operator+=(int num);
	Creature& operator-=(int num);
	void PrintStatus();
	void PrintLog();
};