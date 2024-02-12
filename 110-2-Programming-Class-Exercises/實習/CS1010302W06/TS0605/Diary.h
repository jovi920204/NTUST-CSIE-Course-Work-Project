// Name: ±i∫Õ≈Ô
// Date: March, 27 , 2022  
// Last Update: March, 27 , 2022  
// Problem statement: Observation Diary
#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Diary {

public:
	static void NewDay(string _day);
	static void NewEvent(string name, string something);
	static vector<string> day;
	static map<int, map<string, vector<string>>> eventList;
	//        dayIndex   name     content
};