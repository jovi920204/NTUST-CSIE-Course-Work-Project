// Name: ±i∫Õ≈Ô
// Date: April, 1 , 2022  
// Last Update: April, 1 , 2022  
// Problem statement: Form Word
#include "Form.h"


Form::Form()
{
	word = "";
	fileName = "";

}

void Form::SetInputWord(string inputWord)
{
	word = inputWord;
}

void Form::ProcessInputWord()
{
	for (int i = 0; i < word.length(); i++) {
		//cout << word[i] << endl;
		if (isupper(word[i])) {
			word[i] = tolower(word[i]);
		}
	}
}

void Form::SetFileName(string fileName)
{
	this->fileName = fileName;
}

void Form::Load_CompareWord()
{
	ifstream file(fileName);
	string input;
	map<char, int> wordCount;
	for (int i = 0; i < word.length(); i++) {
		wordCount[word[i]]++;
	}
	while (file >> input){
		map<char, int> inputCount;
		bool validFlag = 1;
		for (int i = 0; i < input.length(); i++) {
			inputCount[input[i]]++;
			if (wordCount[input[i]] == 0 || inputCount[input[i]] > wordCount[input[i]]) {
				validFlag = 0;
				break;
			}
		}
		if (validFlag) {
			valid.push_back(input);
		}

	}
}

void Form::PrintFoundWords()
{
	for (auto val : valid) {
		cout << val << endl;
	}
}
