// Name: ±i∫Õ≈Ô
// Date: May, 27 , 2022  
// Last Update: May , 27 , 2022  
// Problem statement: STL
#include <iostream>
#include <map>
#include <fstream>
#include <string>
using namespace std;

int main() {
	// use ifstream to recive the file
	ifstream inputFile("name.txt");
	// use map in STL to store variable, and avoid repeat name
	map<string, int> nameList;
	while (inputFile.good()) {
		string name;
		// read the content in file with getline() syntax.
		getline(inputFile, name);
		nameList[name]++;
	}
	// file has to be closed. 
	inputFile.close();
	for (auto val : nameList) {
		// if name is empty, we don't output
		if (val.first.empty())
			continue;
		cout << val.first << endl;
	}
	return 0;
}