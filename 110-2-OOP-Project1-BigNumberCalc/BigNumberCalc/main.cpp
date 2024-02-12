// Project: 
//		110-2 Project1 大數計算機 BigNumberCalculator
// 
// Contributors: 
//		B11015034 林信佑 (CCcat134312)
//		B11015030 張睿麟 (jovi920204)
//		B11030232 孫文浩 (haha4mela)
// 
// Github URL: 
//		https://github.com/CCcat134312/BigNumberCalc
// 
// Date: 
//		2022/04/19
// 
// Last Update: 
//		2022/05/05
#include <iostream>

#include "BigNumber.h"
#include "FrontEndAnalyze.h"

using namespace std;
int main(int argc, char* argv[])
{
	string input;
	while (getline(cin, input))
		init(input);
	return 0;
}