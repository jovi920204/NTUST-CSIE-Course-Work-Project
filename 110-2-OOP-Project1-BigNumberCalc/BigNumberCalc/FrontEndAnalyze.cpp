#include "FrontEndAnalyze.h"

bool inputIsValid(std::string input)
{
	if (input.empty())
	{
		std::cout << "Error: Input is empty." << std::endl;
		return false;
	}
	int dotNumber = 0;
	std::string name = "";
	bool alphaFlag = false, invalidSymbol = false, dotFlag = false, varNotExistFlag = false;
	// alpha or not symbol of operation is unacceptable.
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '.')
		{
			dotNumber++;
			if (dotNumber > 1)
				dotFlag = true;
		}
		else if (isdigit(input[i]))
		{
			if (alphaFlag) {
				name += input[i];
			}
			continue;
		}
		else if (isSymbol(input[i]) || input[i] == ' ')
		{
			dotNumber = 0;
			alphaFlag = false;
			if (!name.empty()) {
				if (var.find(name) == var.end()) {
					std::cout << "Error: Can not find the variable \" " << name << " \"." << std::endl;
					varNotExistFlag = true;
				}
			}
			name = "";
			continue;
		}
		else if (isalpha(input[i])) {
			alphaFlag = true;
			name += input[i];
		}
		//else if (isalpha(input[i]))
		//	alphaFlag = true;
		else
			invalidSymbol = true;
	}
	if (varNotExistFlag || invalidSymbol || dotFlag)
	{
		//if (varNotExistFlag)
		//	std::cout << "Error: Input is invalid, using alpha." << std::endl;

		if (invalidSymbol)
			std::cout << "Error: Input is invalid, using invalid symbol" << std::endl;

		if (dotFlag)
			std::cout << "Error: Number of dot in input have more then one." << std::endl;
		return false;
	}

	return isEquationValid(input);
}

std::string replace(std::string input)
{
	std::string output = "";
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '+')
			output += " + ";
		else if (input[i] == '-')
			output += " - ";
		else if (input[i] == '*')
			output += " * ";
		else if (input[i] == '/')
			output += " / ";
		else if (input[i] == '(')
			output += " ( ";
		else if (input[i] == ')')
			output += " ) ";
		else if (input[i] == '!')
			output += " ! ";
		else if (input[i] == '^')
			output += " ^ ";
		else if (input[i] == '%')
			output += " % ";
		else if (input[i] == '=')
			output += " = ";
		else
			output += input[i];
	}
	return output;
}

bool isSymbol(char in)
{
	if (in == '+' || in == '-' || in == '*' || in == '/' ||
		in == '(' || in == ')' || in == '^' || in == '%' ||
		in == '!')
	{
		return true;
	}
	return false;
}

std::string format(std::string input)
{
	std::string output = replace(input);
	int prevIndex = 0, nextIndex = 0;
	bool warningFlag = 0;
	while (nextIndex < output.size() && prevIndex < output.size())
	{
		if (output[prevIndex] == '+' || output[prevIndex] == '-')
		{
			nextIndex = prevIndex + 1;
			while (nextIndex < output.size() && (output[nextIndex] != '+' && output[nextIndex] != '-'))
			{
				if (output[nextIndex] != ' ')
				{
					prevIndex = nextIndex;
					break;
				}
				nextIndex++;
			}
			// Simplification
			if (output[prevIndex] == '+' && output[nextIndex] == '+')
			{
				output[nextIndex] = ' ';
				warningFlag = true;
			}

			else if (output[prevIndex] == '+' && output[nextIndex] == '-')
			{
				output[prevIndex] = '-';
				output[nextIndex] = ' ';
				warningFlag = true;
			}
			else if (output[prevIndex] == '-' && output[nextIndex] == '+')
			{
				output[prevIndex] = '-';
				output[nextIndex] = ' ';
				warningFlag = true;
			}
			else if (output[prevIndex] == '-' && output[nextIndex] == '-')
			{
				output[prevIndex] = '+';
				output[nextIndex] = ' ';
				warningFlag = true;
			}
		}
		else
			prevIndex++;
	}
	if (warningFlag)
		std::cout << "Warning: + or - the way you used may cause some incorrect answer, please add ( and ) in euqatin when you enter." << std::endl;
	return output;
}

int priority(std::string alpha)
{
	if (alpha == "+" || alpha == "-")
		return 1;

	if (alpha == "*" || alpha == "/")
		return 2;

	if (alpha == "^")
		return 3;

	if (alpha == "!")
		return 4;

	return 0;
}

// this algorithm please refer the README.md file.
BigNumber convert(std::string infix)
{
	//std::cout << "convet input = " << infix << std::endl;
	std::stack<std::string> op;
	std::stack<BigNumber> num;
	std::stringstream ss;
	std::string temp;
	bool isSign = 1;
	bool variableError = 0;
	ss << infix;
	while (ss.good())
	{

		ss >> temp;
		if (ss.fail())
			break;

		if (isBigNumber(temp))
		{
			isSign = 0;
			BigNumber tempBN(temp);

			num.push(tempBN);
		}
		else if (isVariable(temp)) {
			isSign = 0;
			num.push(var[temp]);
		}
		else
		{
			if (temp == "(")
			{
				op.push(temp);
				isSign = 1;
			}
			else if (temp == ")")
			{
				if (op.empty())
				{
					std::cout << "Error: Input is invalid, using symbol of operation improper" << std::endl;
					return BigNumber();
				}
				while (op.top() != "(")
				{
					if (op.top() == "!")
					{
						BigNumber a;
						a = factorial(num.top());
						num.pop();
						num.push(a);
					}
					else
					{
						if (num.size() < 2)
						{
							std::cout << "Error: Input is invalid, using symbol of operation improper" << std::endl;
							return BigNumber();
						}
						else
						{
							BigNumber a, b;
							b = num.top();
							num.pop();
							a = num.top();
							num.pop();
							num.push(Calculate(a, b, op.top()));
						}
					}
					op.pop();
				}
				op.pop();
			}
			else
			{
				// preSolve
				// to judge is add and sub or positive and negative
				if (isSign && temp == "+")
				{
					BigNumber a("1");
					op.push("*");
					num.push(a);
				}
				else if (isSign && temp == "-")
				{
					BigNumber a("-1");
					op.push("*");
					num.push(a);
				}
				else	// is symbol of operation
				{
					while (!op.empty() && priority(temp) <= priority(op.top()))
					{
						if (op.top() == "!")
						{
							if (num.empty())
							{
								std::cout << "Error: Input is invalid, using symbol of operation improper" << std::endl;
								return BigNumber();
							}
							BigNumber a;
							a = factorial(num.top());
							num.pop();
							num.push(a);
						}
						else
						{
							if (num.size() < 2)
							{
								std::cout << "Error: Input is invalid, using symbol of operation improper" << std::endl;
								return BigNumber();
							}
							BigNumber a, b;
							b = num.top();
							num.pop();
							a = num.top();
							num.pop();
							num.push(Calculate(a, b, op.top()));
						}
						op.pop();
					}
					op.push(temp);
				}
			}
		}
	}
	// clear op stack
	while (!op.empty())
	{
		if (op.top() == "!")
		{
			if (num.empty())
			{
				std::cout << "Error: Input is invalid, using symbol of operation improper" << std::endl;
				return BigNumber();
			}
			BigNumber a;
			a = factorial(num.top());
			num.pop();
			num.push(a);
		}
		else
		{
			if (num.size() < 2)
			{
				std::cout << "Error: Input is invalid, using symbol of operation improper" << std::endl;
				return BigNumber();
			}
			BigNumber a, b;
			b = num.top();
			num.pop();
			a = num.top();
			num.pop();
			num.push(Calculate(a, b, op.top()));
		}
		op.pop();
	}

	if (num.size() == 0)
	{
		std::cout << "Error: Input is empty." << std::endl;
		return BigNumber();
	}
	else if (num.size() != 1) {
		std::cout << "Error: Input is incorrect." << std::endl;
		num.pop();
		//std::cout << "num.top() = " << num.top() << std::endl;
		//std::cout << "op.top() = " << op.top() << std::endl;
		return BigNumber();
	}
	//std::cout << "convet output = " << num.top() << std::endl;
	return num.top();
}

bool isBigNumber(std::string num)
{
	for (int i = 0; i < num.size(); i++)
	{
		if (!(isdigit(num[i]) || num[i] == '.'))	// isn't digit or '.' 
			return false;
	}
	return true;
}

BigNumber Calculate(const BigNumber& a, const BigNumber& b, std::string symbol)
{
	BigNumber result;
	if (symbol == "+")
		result = a + b;
	else if (symbol == "-")
		result = a - b;
	else if (symbol == "*")
		result = a * b;
	else if (symbol == "/")
		result = a / b;
	else if (symbol == "%")
		result = a % b;
	else if (symbol == "^")
		result = power(a, b);
	return result;
}

bool isVariable(std::string str) {
	if (var.find(str) != var.end()) {
		return 1;
	}
	return 0;
}

bool isCommand(std::string& input) {

	int equalIndex = -1;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '=') {
			equalIndex = i;
			break;
		}
	}
	std::string command;
	std::string type;
	std::string variableName;
	std::string equation;
	std::stringstream ss;
	ss << input;
	ss >> command;
	if (command == "set") {
		ss >> type;
		ss >> variableName;
		if (!isVariableNameValid(variableName))
		{
			std::cout << "Error: The variable name is not valid." << std::endl;
			return 1;
		}
		if (type == "integer" || type == "decimal")
		{
			if (equalIndex == -1) {
				var[variableName] = BigNumber();
				std::cout << "The variable \" " << variableName << " \" assign " << var[variableName] << "." << std::endl;
			}
			else {
				for (int i = equalIndex + 1; i < input.size(); i++)
				{
					equation += input[i];
				}
				if (type == "integer") {
					if (inputIsValid(equation)) {
						var[variableName] = floatToInt(convert(equation));
						std::cout << "The variable \" " << variableName << " \" assign " << var[variableName] << "." << std::endl;
					}
					else {
						std::cout << "Error: Input is incorrect." << std::endl;
					}
				}
				else if (type == "decimal") {
					if (inputIsValid(equation)) {
						var[variableName] = intToFloat(convert(equation));
						std::cout << "The variable \" " << variableName << " \" assign " << var[variableName] << "." << std::endl;
					}
					else {
						std::cout << "Error: Input is incorrect." << std::endl;
					}
				}
			}
		}
		else {
			std::cout << "Error: The type, which you entered, is invalid." << std::endl;
		}
		return 1;
	}
	else if (command == "get") {
		ss >> variableName;
		if (var.find(variableName) == var.end()) {
			std::cout << "Error: The variable name is not found." << std::endl;
		}
		else {
			std::cout << "The variable \" " << variableName << " \" is " << var[variableName] << "." << std::endl;
		}
		return 1;
	}
	else if (command == "delete") {
		ss >> variableName;
		if (var.find(variableName) == var.end()) {
			std::cout << "Error: The variable name is not found." << std::endl;
		}
		else {
			var.erase(variableName);
			std::cout << "The variable \" " << variableName << " \" is deleted." << std::endl;
		}
		return 1;
	}
	else if (command == "list") {
		if (!var.empty())
			for (const auto& val : var)
				std::cout << val.first << " " << val.second << std::endl;
		else
		{
			std::cout << "Message: You didn't assign any variable." << std::endl;
		}
		return 1;
	}
	else if (command == "clear") {
		var.clear();
		std::cout << "Message: The variables is cleared." << std::endl;
	}
	else
		return 0;
}

bool isAssign(std::string input) {
	int equalIndex = -1;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '=') {
			equalIndex = i;
			break;
		}
	}
	if (equalIndex == -1) {
		return 0;
	}
	else {
		std::string target;
		std::string equation;
		for (int i = 0; i < equalIndex; i++) {
			if (input[i] != ' ')
				target += input[i];
		}
		if (var.find(target) == var.end())
		{
			std::cout << "Error: Can not find the variable \" " << target << " \"." << std::endl;
			return 0;
		}
		for (int i = equalIndex + 1; i < input.size(); i++) {
			equation += input[i];
		}
		if (inputIsValid(equation)) {
			if(var[target].getType())	// 1: int
				var[target] = floatToInt(convert(equation));
			else	// 0: float
				var[target] = intToFloat(convert(equation));

			std::cout << target << " = " << var[target] << std::endl;
		}
		else {
			std::cout << "Error: Input is incorrect." << std::endl;
		}
		return 1;
	}
}

void init(std::string input)
{
	input = format(input);
	//std::cout << "after format = " << input << std::endl;

	if (isCommand(input))
	{
		// if is doing the command then continue;
		return;
	}
	else if (isAssign(input)) {
		// if Assign successfully
		return;
	}
	// is equation
	else if (inputIsValid(input)) {
		// if input is valid then do convert;
		//input = "( " + input + " )";
		std::cout << convert(input) << std::endl;
		return;
	}
	else {
		std::cout << "Error: Input is incorrect." << std::endl;
	}

}

bool isVariableNameValid(std::string name) {
	for (int i = 0; i < name.size(); i++) {
		if (isdigit(name[i]) || isalpha(name[i])) {
			continue;
		}
		return 0;
	}
	return 1;
}

bool isEquationValid(std::string input) {
	int pairNum(0);
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '(')
			pairNum++;
		else if (input[i] == ')')
			pairNum--;
		if (pairNum < 0)
			return false;
	}
	if (pairNum != 0)
		return false;

	std::stringstream ss;
	ss << input;

	while (ss.good()) {
		std::string s1, s2;
		ss >> s1;
		if (ss.fail()) {
			return 1;
		}
		ss >> s2;
		if (s1 == "(") {
			//std::cout << "Q" << std::endl;
			if (isSymbol(s2[0]) && (s2 != "+" && s2 != "-" && s2 != "(")) {
				return 0;
			}
		}
		if (s1 == "+") {
			if (isSymbol(s2[0]) && (s2 != "+" && s2 != "-")) {
				return 0;
			}
		}
		if (s1 == ")") {
			if (s2 == "(") {
				return 0;
			}
		}
		if (s1 == "*" || s1 == "/" || s1 == "^" || s1 == "%") {
			if (isSymbol(s2[0]) && s2 != "(") {
				return 0;
			}
		}
	}
	return 1;
}

bool isEquation(std::string input)
{
	int operatorNum(0);
	for (int i = 0; i < input.size(); i++)
	{
		if (isSymbol(input[i]))
			operatorNum++;
	}
	if (operatorNum > 1)	// 1+1+1
		return true;
	else if (operatorNum == 1 && (input[0] != '+' && input[0] != '-'))	// 1+1
		return true;
	return false;
}