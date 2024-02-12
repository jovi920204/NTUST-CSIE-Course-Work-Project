#pragma once
#include "BigNumber.h"

// 判斷輸入的運算式是否合法
// Judge input equation is legel.
bool inputIsValid(std::string);

// Check the char is Symbol of operation or not
bool isSymbol(char);

// 對字串格式化，避免+跟-一元的狀況 Ex. 1+++++1 => 1 + 1
// To format string, avoid situation which + or - is sign not addition or subtraction.
std::string format(std::string);

// replace any op to " op "
std::string replace(std::string);

// 判斷運算符號的優先順序
// Judge the priority of symbol of operation.
int priority(std::string alpha);

// 把數值運算式算出答案
// Calculate the input equation.
BigNumber convert(std::string);

// 判斷輸入的字串是否為BigNumber的格式
// Judge the input string is meets BigNumber format or not.
bool isBigNumber(std::string);

// 計算兩數和一個運算符號
// Calculate two number and one symbol of operation.
BigNumber Calculate(const BigNumber&, const BigNumber&, std::string symbol);

// check the input string is exist or not.
bool isVariable(std::string);

// 儲存變數
// store the variables
static std::map<std::string, BigNumber> var;

//check is commond or not and do
bool isCommand(std::string&);

// initialize
void init(std::string);


// Assign string, like a = b + c.
bool isAssign(std::string);

// check the variable name is valid or not.
bool isVariableNameValid(std::string);

// check the equation is valid or not
bool isEquationValid(std::string);

// check is equation or not
bool isEquation(std::string);