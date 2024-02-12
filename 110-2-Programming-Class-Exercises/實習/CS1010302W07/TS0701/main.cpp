// Name: ±i∫Õ≈Ô
// Date: April, 1 , 2022  
// Last Update: April, 1 , 2022  
// Problem statement: Form Word
#include"Form.h"

int main()
{
	Form form1;
	form1.SetInputWord("SWIMMING"); // set input
	form1.ProcessInputWord(); // process input
	form1.SetFileName("words.txt"); // set file name
	form1.Load_CompareWord(); // read-in data and compare
	form1.PrintFoundWords(); // print answers
	return 0;
}