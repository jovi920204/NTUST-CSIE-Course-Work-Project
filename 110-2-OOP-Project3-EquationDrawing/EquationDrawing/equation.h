#ifndef EQUATION_H
#define EQUATION_H
#pragma once
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <stack>
#include <cmath>

class Equation
{
private:
    std::string oriEquation;	// origin equation
    std::string variable;
    std::string formula;

    static std::unordered_map <std::string, std::function<double(double, double)>> operators;
    static std::unordered_map<std::string, std::string> variableNames;
    static std::unordered_map<std::string, int> priority;
    static std::unordered_set<char> mathSign;
    static std::unordered_set<std::string> triFunc;

    bool isTriFunc(std::string name) { return triFunc.find(name) != triFunc.end(); };
    void isEquationGood(std::string e);

    bool isMathSign(char c) { return mathSign.find(c) != mathSign.end(); };
    std::string changeUnaryOperator(std::string formula);
    std::string parseVariableName(std::string rawStr);
    std::string changeVariable(std::string formula);

    std::string inorderToPostorder(std::string fixed);
    bool checkPostorderElement(std::string element);
    double calculatePostorder(std::string postorder, double arg = 0);

public:
    Equation();
    Equation(std::string _e);
    Equation(const Equation& _e);

    void printVariableList();
    void removeVariable(std::string name);
    void clearVariableList();

    std::string getOriEquation() { return oriEquation; }
    std::string getVariable() { return variable; }
    std::string getFormula() { return formula; }

    void checkAndInit();
    // common function: y = f(x) or x = f(y)
    // -> e.g. y=x+1, x=1 -> return 2
    // -> e.g. x=y+2, y=2 -> return 4
    // variable function: a
    // -> if it have 'x' in function e.g. a=x+1, x=1 -> return 2
    // -> if it is constant number e.g. a=123, (x=_) -> return 123
    double calculate(double arg = 0);

    friend std::istream& operator>>(std::istream& is, Equation& e);
};



#endif // EQUATION_H
