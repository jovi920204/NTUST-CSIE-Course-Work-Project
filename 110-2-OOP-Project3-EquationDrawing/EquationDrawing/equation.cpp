#include "Equation.h"

std::unordered_map<std::string, std::string> Equation::variableNames = {};
std::unordered_map<std::string, int> Equation::priority = {
    {"+",1}, {"-",1}, {"*",2}, {"/",2},
    {"^",3}, {"#",4}, {"~",4},
    {"sin",5}, {"cos",5}, {"tan",5},
    {"cot",5}, {"sec",5}, {"csc",5}
};
std::unordered_map<std::string, std::function<double(double, double)>> Equation::operators = {
    {"+",[](double numA, double numB) {return numA + numB; }},
    {"-",[](double numA, double numB) {return numA - numB; }},
    {"*",[](double numA, double numB) {return numA * numB; }},
    {"/",[](double numA, double numB) {return numA / numB; }},
    {"^",[](double numA, double numB) {return pow(numA , numB); }},
    {"#",[](double numA, double numB) {return +numB; }},
    {"~",[](double numA, double numB) {return -numB; }},
    {"sin",[](double numA, double numB) {return sin(numB); }},
    {"cos",[](double numA, double numB) {return cos(numB); }},
    {"tan",[](double numA, double numB) {return tan(numB); }},
    {"cot",[](double numA, double numB) {return 1 / tan(numB); }},
    {"sec",[](double numA, double numB) {return 1 / cos(numB); }},
    {"csc",[](double numA, double numB) {return 1 / sin(numB); }}
};
std::unordered_set<char> Equation::mathSign = { '+','-','*','/','^','(',')' };
std::unordered_set<std::string> Equation::triFunc = { "sin","cos","tan","cot","sec","csc" };

void Equation::isEquationGood(std::string e)
{
    if (std::count(e.begin(), e.end(), '=') != 1)
        throw std::string("equal sign must have 1 and only have 1.");

    int bracket(0);
    for (char c : e)
    {
        if (c == '(')
            bracket++;
        else if (c == ')')
            bracket--;
        if (bracket < 0)
            throw std::string("invalid brackets.");
    }
    if (bracket != 0 || e.find("()") != std::string::npos)
        throw std::string("invalid brackets.");

    int equalIndex = e.find('=');
    std::string variableName = e.substr(0, equalIndex);
    if (variableName == "y" || variableName == "x")
        return;

    for (auto op : operators)
    {
        if (variableName.find(op.first) != std::string::npos)
            throw std::string("variable name used reserve word.");
    }
    for (char c : variableName)
    {
        if (!isalpha(c))
            throw std::string("variable name must be all alphabet.");
    }

    if (variableNames.find(variableName) != variableNames.end())
        throw std::string("repeat variable name.");
}

std::string Equation::changeUnaryOperator(std::string formula)
{
    std::string result = "";
    if (formula[0] == '+')
        result += '#';
    else if (formula[0] == '-')
        result += '~';
    else
        result += formula[0];
    for (int i = 1; i < formula.size(); i++)
    {
        if ((formula[i] == '+' || formula[i] == '-') &&
            !isdigit(formula[i - 1]) && formula[i - 1] != ')' &&
            formula[i - 1] != 'x' && formula[i - 1] != 'y')
        {
            result += (formula[i] == '+' ? '#' : '~');
            continue;
        }
        result += formula[i];
    }
    return result;
}

std::string Equation::parseVariableName(std::string rawStr)
{
    std::string result("");
    for (int i = 0; i < rawStr.size() && isalpha(rawStr[i]) &&
        !(i + 2 < rawStr.size() && isTriFunc(rawStr.substr(i, 3))); i++)
    {
        result += rawStr[i];
    }
    return result;
}

std::string Equation::changeVariable(std::string formula)
{
    std::string result("");
    for (int i = 0; i < formula.size(); i++)
    {
        if (isdigit(formula[i]))
        {
            for (; i < formula.size() && !isMathSign(formula[i]); i++)
                result += formula[i];
            i--;
        }
        else if (isMathSign(formula[i]))
        {
            result += formula[i];
        }
        else if (i + 2 < formula.size() && isTriFunc(formula.substr(i, 3)))
        {
            result += formula.substr(i, 3);
            i += 2;
        }
        else // variable
        {
            std::string name = parseVariableName(formula.substr(i, formula.size()));
            i += (name.size() - 1);

            if (name != "x" && name != "y")
            {
                if (variableNames.find(name) == variableNames.end())
                    throw std::string("undefine variable.");
                result += "(" + variableNames[name] + ")";
                continue;
            }
            result += name;
        }
    }
    return result;
}

std::string Equation::inorderToPostorder(std::string fixed)
{
    std::string result = "";
    std::stack<std::string> s;
    for (int i = 0; i < fixed.size(); i++)
    {
        std::string temp(1, fixed[i]);
        std::unordered_set<std::string> commonOp = { "+","-","*","/","^","#","~" };
        if (commonOp.find(temp) != commonOp.end())
        {
            while (!s.empty() && priority[s.top()] >= priority[temp])
            {
                result += s.top();
                result += ' ';
                s.pop();
            }
            s.push(temp);
        }
        else if (i + 2 < fixed.size() && isTriFunc(fixed.substr(i, 3)))	// trigonometric functions
        {
            temp = fixed.substr(i, 3);
            while (!s.empty() && priority[s.top()] >= priority[temp])
            {
                result += s.top();
                result += ' ';
                s.pop();
            }
            s.push(temp);
            i += 2;
        }
        else if (temp == "(")
        {
            s.push(temp);
        }
        else if (temp == ")")
        {
            while (s.top() != "(")
            {
                result += s.top();
                result += ' ';
                s.pop();
            }
            s.pop();
        }
        else
        {
            for (; i < fixed.size() && !isMathSign(fixed[i]); i++)
                result += fixed[i];
            result += ' ';
            i--;
        }
    }
    while (!s.empty())
    {
        result += s.top();
        result += ' ';
        s.pop();
    }
    return result;
}

bool Equation::checkPostorderElement(std::string element)
{
    // is variable or not
    if (variableNames.find(element) != variableNames.end()
        || element == "x" || element == "y")
        return true;

    // judge element is digit or not
    std::regex digitRule("(\\d)+(\\.)?(\\d)*");
    if (std::regex_match(element, digitRule))
        return true;

    if (operators.find(element) != operators.end())
        return true;

    // isn't a digit and isn't a variable either.
    return false;
}

double Equation::calculatePostorder(std::string postorder, double arg)
{
    std::stringstream ss(postorder);
    std::stack<double> nums;
    while (!ss.eof())
    {
        std::string element;
        ss >> element;
        if (element.empty())	// avoid empty string
            continue;

        if (!checkPostorderElement(element))
            throw std::string("failed to parse equation.");

        if (isdigit(element[0])) // digit
        {
            double num;
            std::stringstream convert;
            convert << element;
            convert >> num;
            nums.push(num);
        }
        else if (element == "x" || element == "y")
        {
            nums.push(arg);
        }
        else // operator
        {
            double front(0), back(0);
            if (nums.empty())
                throw std::string("use operator in wrong way.");
            back = nums.top();
            nums.pop();

            // binary operator
            std::unordered_set<std::string> binaryOp = { "+","-","*","/","^" };
            if (binaryOp.find(element) != binaryOp.end())
            {
                if (nums.empty())
                    throw std::string("operator error.");
                front = nums.top();
                nums.pop();
            }
            nums.push(operators[element](front, back));
        }
    }
    return nums.top();
}

Equation::Equation() :oriEquation(""), variable(""), formula("")
{
}

Equation::Equation(std::string _e) : oriEquation(_e), variable(""), formula("")
{
}

Equation::Equation(const Equation& _e)
{
    this->oriEquation = _e.oriEquation;
    this->variable = _e.variable;
    this->formula = _e.formula;
}

void Equation::printVariableList()
{
    std::cout << std::string(35, '-') << '\n';
    for (auto i : variableNames)
        std::cout << i.first << ": " << i.second << '\n';
    std::cout << std::string(35, '-') << '\n';
}

void Equation::removeVariable(std::string name)
{
    auto targetIt = variableNames.find(name);
    if (targetIt == variableNames.end())
        throw std::string("fail to find the variable.");
    variableNames.erase(targetIt);
}

void Equation::clearVariableList()
{
    variableNames.clear();
}

void Equation::checkAndInit()
{
    isEquationGood(oriEquation);	// check define variable, brackets
    // no error -> may be good equation
    int equalIndex = oriEquation.find('=');
    variable = oriEquation.substr(0, equalIndex);
    formula = oriEquation.substr(equalIndex + 1, oriEquation.size());
}

double Equation::calculate(double arg)
{
    std::string fixedEquation = changeVariable(formula);
    fixedEquation = changeUnaryOperator(fixedEquation);

    std::string postorder;
    double result;
    // is a constant function ?
    if ((fixedEquation.find('x') == std::string::npos && variable == "y") ||
        (fixedEquation.find('y') == std::string::npos && variable == "x"))
    {
        postorder = inorderToPostorder(fixedEquation);
        result = calculatePostorder(postorder);
        std::stringstream convert;
        convert << std::fixed << result;
        std::string constNum;
        convert >> constNum;
        if (variable != "y" && variable != "x")
            variableNames[variable] = constNum;
    }
    else
    {
        if (variable != "y" && variable != "x")
            variableNames[variable] = fixedEquation;
        postorder = inorderToPostorder(fixedEquation);
        result = calculatePostorder(postorder, arg);
    }
    return result;
}

std::istream& operator>>(std::istream& is, Equation& e)
{
    is >> e.oriEquation;
    return is;
}
