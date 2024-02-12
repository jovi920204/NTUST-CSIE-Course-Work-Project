// Name: ±i∫Õ≈Ô
// Date: March, 27 , 2022  
// Last Update: March, 27 , 2022  
// Problem statement: Observation Diary
#include "Diary.h"
#include "Creature.h"

void Diary::NewDay(string _day)
{
	day.push_back(_day);
}
void Diary::NewEvent(string name, string something) {
	eventList[day.size() - 1][name].push_back(something);
}
vector<string> Diary::day;
map<int, map<string, vector<string>>> Diary::eventList;
//  dayIndex   name     content
