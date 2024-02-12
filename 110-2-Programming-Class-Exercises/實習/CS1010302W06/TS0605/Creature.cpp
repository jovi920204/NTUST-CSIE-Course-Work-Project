// Name: ±iºÍÅï
// Date: March, 27 , 2022  
// Last Update: March, 27 , 2022  
// Problem statement: Observation Diary
#include "Creature.h"
Creature::Creature(string _name)
{
	name = _name;
	startDayIndex = Diary::day.size()-1;
}
Creature::Creature(string _name, Creature c)
{
	name = _name;
	mp = c.mp;
	startDayIndex = Diary::day.size()-1;
}
Creature& Creature::operator[](string body)
{
	currentBody = body;
	return *this;
	// TODO: insert return statement here
}

Creature& Creature::operator=(int value)
{
	int original = mp[currentBody];
	mp[currentBody] = value;
	string log;
	if (original == 0 && value == 0) {
		return *this;
	}
	else if (original == 0) {
		log = name + "'s " + currentBody + " appeared (0 -> " + to_string(value) + ").";
	}
	else if (original < value) {
		log = name + "'s " + currentBody + " increased (" + to_string(original) + " -> " + to_string(mp[currentBody]) + ").";
	}
	else if (original > value) {
		log = name + "'s " + currentBody + " decreased (" + to_string(original) + " -> " + to_string(value) + ").";
	}
	else {
		return *this;
	}
	Diary::NewEvent(name, log);
	return *this;
	// TODO: insert return statement here
}

Creature& Creature::operator+=(int value)
{
	int original = mp[currentBody];
	mp[currentBody] += value;
	string log;
	if (original > mp[currentBody]) {
		log = name + "'s " + currentBody + " decreased (" + to_string(original) + " -> " + to_string(mp[currentBody]) + ").";
	}
	else if (original == 0) {
		log = name + "'s " + currentBody + " appeared (0 -> " + to_string(mp[currentBody]) + ").";
	}
	else if (original < mp[currentBody]) {
		log = name + "'s " + currentBody + " increased (" + to_string(original) + " -> " + to_string(mp[currentBody]) + ").";
	}
	else {
		return *this;
	}

	Diary::NewEvent(name, log);
	return *this;
	// TODO: insert return statement here
}

Creature& Creature::operator-=(int value)
{
	int original = mp[currentBody];
	mp[currentBody] -= value;
	string log;
	if (original > mp[currentBody]) {
		log = name + "'s " + currentBody + " decreased (" + to_string(original) + " -> " + to_string(mp[currentBody]) + ").";
	}
	else if (original == 0) {
		log = name + "'s " + currentBody + " appeared (0 -> " + to_string(mp[currentBody]) + ").";
	}
	else if (original < mp[currentBody]) {
		log = name + "'s " + currentBody + " increased (" + to_string(original) + " -> " + to_string(mp[currentBody]) + ").";
	}
	else {
		return *this;
	}
	Diary::NewEvent(name, log);
	return *this;
	// TODO: insert return statement here
}

void Creature::PrintStatus()
{
	cout << name << "'s status:" << endl;
	for (auto val : mp) {
		if (val.second != 0) {
			cout << val.first << " * " << val.second << endl;
		}
	}
	cout << endl;
}

void Creature::PrintLog()
{
	//map<int, map<string, vector<string>>> eventList
	//  dayIndex   name     content
	cout << name << "'s log:" << endl;
	for (int i = startDayIndex; i < Diary::day.size(); i++) {
		cout << "Day " << Diary::day[i] << endl;
		for (int j = 0; j < Diary::eventList[i][this->name].size(); j++) {
			if (Diary::eventList[i][this->name][j] == "") {
				continue;
			}
			else {
				cout << Diary::eventList[i][this->name][j] << endl;
			}
		}
	}
	cout << endl;
}