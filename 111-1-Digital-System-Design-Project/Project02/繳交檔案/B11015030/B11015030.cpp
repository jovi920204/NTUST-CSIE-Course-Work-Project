#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;

void printTerms(vector<string> &table);
void printTable(map<string, vector<string>> &mp);
void termsInit(int inputNum);
void termsExpansion(int inputNum, string currTerm, int index, string original, vector<string> &tempExpandTerms);
vector<vector<string>> classification(vector<string> &tempExpandTerms, int inputNum);
vector<vector<string>> simplify(int inputNum, vector<vector<string>> &tempClassTerms);
int diffOne(string a, string b);
vector<string> expand(string &str, string currStr, int index);
void createPrimeImplicant(map<string, vector<string>> &expandTable, map<string, int> &countTable, int inputNum);
void createEssentialPrimeImplicant(vector<string> &epi, map<string, int> &countTable);
void createPetrickTable(vector<string> &epi, map<string, vector<string>> &expandTable, map<string, vector<string>> &epiTable, map<string, bool> &used, map<string, vector<string>> &piTable, vector<string> &othersTerms);
int countLiterals(vector<string> &result);

vector<string> terms;
vector<string> expandTerms;
vector<string> dontcareTerms;
vector<vector<string>> classTerms;

int main(int argc, char *argv[])
{
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1]);
    output_file.open(argv[2]);
    int inputNum = 0;          // .i
    int outputNum = 0;         // .o
    vector<string> labelName;  // .ilb
    vector<string> outputName; // .ob
    int productNum = 0;        // .p => product term number

    // Read input file
    while (input_file.good())
    {
        string type;
        string name;
        input_file >> type;
        if (type == ".i")
        {
            input_file >> inputNum;
        }
        else if (type == ".o")
        {
            input_file >> outputNum;
        }
        else if (type == ".ilb")
        {
            for (int i = 0; i < inputNum; i++)
            {
                string name;
                input_file >> name;
                labelName.push_back(name);
            }
        }
        else if (type == ".ob")
        {
            for (int i = 0; i < outputNum; i++)
            {
                string name;
                input_file >> name;
                outputName.push_back(name);
            }
        }
        else if (type == ".p")
        {
            input_file >> productNum;
            for (int i = 0; i < productNum * 2; i++)
            {
                string t;
                string r;
                input_file >> t >> r;
                if (r == "1" || r == "-")
                {
                    terms.push_back(t);
                    if (r == "-")
                        dontcareTerms.push_back(t);
                }
            }
        }
        else if (type == ".e")
        {
            continue;
        }
    }

    // Expand all possible of each terms
    termsInit(inputNum);
    // Classify every terms with number of 1s
    classTerms = classification(expandTerms, inputNum);

    // Quine–McCluskey algorithm
    // Simplify with Quine–McCluskey algorithm
    classTerms = simplify(inputNum, classTerms);
    // Store all the Prime Implicant
    map<string, vector<string>> expandTable;
    map<string, int> countTable;
    createPrimeImplicant(expandTable, countTable, inputNum);
    // Extract Essential Prime Implicant from Prime Implicant
    vector<string> epi; // Essential Prime Implicant
    createEssentialPrimeImplicant(epi, countTable);

    // Petrick Algorithm
    map<string, vector<string>> epiTable;
    map<string, vector<string>> piTable;
    vector<string> othersTerms;
    map<string, bool> used;
    createPetrickTable(epi, expandTable, epiTable, used, piTable, othersTerms);
    map<string, string> symbol;
    map<char, string> symbolInverse;
    int s = 0;

    // Using a-z to represent the PI terms, and sort them by dictionary order
    // So that we can find duplicate words and delete it, let every sum of product terms be unique
    for (auto val : piTable)
    {
        symbol[val.first] = 'a' + s;
        symbolInverse['a' + s] = val.first;
        s++;
    }
    vector<vector<string>> formula(othersTerms.size());
    int count = 0;
    for (auto val : othersTerms)
    {
        for (auto N : piTable)
        {
            if (find(N.second.begin(), N.second.end(), val) != N.second.end())
            {
                formula[count].push_back(symbol[N.first]);
            }
        }
        count++;
    }

    while (formula.size() > 1)
    {
        vector<string> tempVec;
        for (int i = 0; i < formula[0].size(); i++)
        {
            for (int j = 0; j < formula[1].size(); j++)
            {
                tempVec.push_back(formula[0][i] + formula[1][j]);
            }
        }
        formula[0] = tempVec;
        formula.erase(formula.begin() + 1);
    }

    // Expand all the possible PI terms and choose the shortes one, store in result array
    vector<string> result;
    if (formula.size() != 0)
    {
        int minLength = 1000000;
        for (auto &val : formula[0])
        {
            sort(val.begin(), val.end());
            for (int i = 0; i < val.size(); i++)
            {
                if (val[i] == val[i + 1])
                {
                    val = val.substr(0, i) + val.substr(i + 1, val.size());
                    i--;
                }
            }
            if (minLength > val.size())
                minLength = val.size();
        }
        sort(formula[0].begin(), formula[0].end());
        for (int i = 0; i < formula[0].size() - 1; i++)
        {
            if (formula[0][i] == formula[0][i + 1] || formula[0][i].size() > minLength)
            {
                formula[0].erase(formula[0].begin() + i);
                i--;
            }
        }
        for (auto i : formula[0][0])
        {
            result.push_back(symbolInverse[i]);
        }
    }
    for (auto val : epiTable)
    {
        result.push_back(val.first);
    }

    // Write output text file
    output_file << ".i " << inputNum << endl;
    output_file << ".o " << outputNum << endl;
    output_file << ".lib";
    for (auto val : labelName)
    {
        output_file << " " << val;
    }
    output_file << endl;
    output_file << ".ob";
    for (auto val : outputName)
    {
        output_file << " " << val;
    }
    output_file << endl;
    output_file << ".p " << result.size() << endl;
    for (auto val : result)
    {
        output_file << val << " 1" << endl;
    }
    output_file << ".e" << endl;

    cout << "Total number of terms: " << result.size() << endl;
    cout << "Total number of literals: " << countLiterals(result) << endl;
    return 0;
}

void printTerms(vector<string> &table)
{
    for (auto val : table)
    {
        cout << val << endl;
    }
}

void printTable(map<string, vector<string>> &mp)
{
    for (auto val : mp)
    {
        cout << val.first << " : ";
        for (auto val2 : val.second)
        {
            cout << val2 << " ";
        }
        cout << endl;
    }
}

void termsInit(int inputNum)
{
    for (auto val : terms)
    {
        string currTerm = "";
        termsExpansion(inputNum, currTerm, 0, val, expandTerms);
    }
    classTerms.resize(inputNum + 1);
}

void termsExpansion(int inputNum, string currTerm, int index, string original, vector<string> &tempExpandTerms)
{
    if (index == inputNum)
    {
        auto it = std::find(tempExpandTerms.begin(), tempExpandTerms.end(), currTerm);
        if (it == tempExpandTerms.end())
            tempExpandTerms.push_back(currTerm);
        return;
    }
    if (original[index] == '-')
    {
        termsExpansion(inputNum, currTerm + '0', index + 1, original, tempExpandTerms);
        termsExpansion(inputNum, currTerm + '1', index + 1, original, tempExpandTerms);
    }
    else
    {
        termsExpansion(inputNum, currTerm + original[index], index + 1, original, tempExpandTerms);
    }
}

vector<vector<string>> classification(vector<string> &tempExpandTerms, int inputNum)
{
    vector<vector<string>> retTerms(inputNum + 1);
    for (auto val : tempExpandTerms)
    {
        int count = 0;
        for (int i = 0; i < val.size(); i++)
        {
            if (val[i] == '1')
                count++;
        }
        retTerms[count].push_back(val);
    }
    return retTerms;
}

vector<vector<string>> simplify(int inputNum, vector<vector<string>> &tempClassTerms)
{
    int total = 0;
    vector<vector<bool>> used(tempClassTerms.size());
    for (int i = 0; i < tempClassTerms.size(); i++)
    {
        total += tempClassTerms[i].size();
        used[i].resize(tempClassTerms[i].size());
    }
    vector<string> newExpandTerms;
    vector<vector<string>> newClassTerms;
    for (int i = 0; i < tempClassTerms.size() - 1; i++)
    {
        for (int now = 0; now < tempClassTerms[i].size(); now++)
        {
            for (int next = 0; next < tempClassTerms[i + 1].size(); next++)
            {
                int loc = diffOne(tempClassTerms[i][now], tempClassTerms[i + 1][next]);
                if (loc != -1)
                {
                    string temp = tempClassTerms[i][now];
                    used[i][now] = 1;
                    used[i + 1][next] = 1;
                    temp[loc] = '-';
                    auto it = std::find(newExpandTerms.begin(), newExpandTerms.end(), temp);
                    if (it == newExpandTerms.end())
                        newExpandTerms.push_back(temp);
                }
            }
        }
    }
    int unUsed = 0;
    for (int i = 0; i < used.size(); i++)
    {
        for (int j = 0; j < used[i].size(); j++)
        {
            if (used[i][j] == 0)
            {
                unUsed++;
                newExpandTerms.push_back(tempClassTerms[i][j]);
            }
        }
    }
    newClassTerms = classification(newExpandTerms, inputNum);
    // cout << total << " " << unUsed << endl;
    if (total == unUsed)
        return newClassTerms;
    else
        return simplify(inputNum, newClassTerms);
}

int diffOne(string a, string b)
{
    int count = 0;
    int index = -1;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
        {
            count++;
            index = i;
        }
    }
    if (count == 1)
        return index;
    else
        return -1;
}

void createPrimeImplicant(map<string, vector<string>> &expandTable, map<string, int> &countTable, int inputNum)
{
    for (int i = 0; i < expandTerms.size(); i++)
    {
        auto it = find(dontcareTerms.begin(), dontcareTerms.end(), expandTerms[i]);
        if (it == dontcareTerms.end())
            countTable[expandTerms[i]] = 0;
    }
    for (int i = 0; i < classTerms.size(); i++)
    {
        for (auto val : classTerms[i])
        {
            // val = simplified term
            termsExpansion(inputNum, "", 0, val, expandTable[val]);
        }
    }
    for (auto val : expandTable)
    {
        for (auto val2 : val.second)
        {
            auto it1 = find(expandTerms.begin(), expandTerms.end(), val2);
            auto it2 = find(dontcareTerms.begin(), dontcareTerms.end(), val2);
            if (it1 != expandTerms.end() && it2 == dontcareTerms.end())
            {
                countTable[val2]++;
            }
        }
    }
}

void createEssentialPrimeImplicant(vector<string> &epi, map<string, int> &countTable)
{
    for (auto val : countTable)
    {
        if (val.second == 1){
            epi.push_back(val.first);
        }
    }
    
}

void createPetrickTable(vector<string> &epi, map<string, vector<string>> &expandTable, map<string, vector<string>> &epiTable, map<string, bool> &used, map<string, vector<string>> &piTable, vector<string> &othersTerms)
{
    for (auto epiVal : epi) // createEPI
    {
        for (auto expandVal : expandTable)
        {
            auto it = find(expandVal.second.begin(), expandVal.second.end(), epiVal);
            if (it != expandVal.second.end())
            {
                for (auto val : expandVal.second)
                {
                    if (find(dontcareTerms.begin(), dontcareTerms.end(), val) == dontcareTerms.end())
                    {
                        epiTable[expandVal.first].push_back(val);
                        used[val] = true;
                    }
                }
            }
        }
    }
    for (auto exp : expandTerms)
    {
        if (find(dontcareTerms.begin(), dontcareTerms.end(), exp) == dontcareTerms.end() && used[exp] == false)
        {
            for (auto expandVal : expandTable)
            {
                auto it = find(expandVal.second.begin(), expandVal.second.end(), exp);
                if (it != expandVal.second.end())
                {
                    for (auto val : expandVal.second)
                    {
                        if (find(piTable[expandVal.first].begin(), piTable[expandVal.first].end(), val) == piTable[expandVal.first].end() && used[val] == false && find(dontcareTerms.begin(), dontcareTerms.end(), val) == dontcareTerms.end())
                        {
                            piTable[expandVal.first].push_back(val);
                            if (find(othersTerms.begin(), othersTerms.end(), val) == othersTerms.end())
                            {
                                othersTerms.push_back(val);
                            }
                        }
                    }
                }
            }
        }
    }
}

int countLiterals(vector<string> &result)
{
    int count = 0;
    for (auto val : result)
    {
        for (auto i : val)
        {
            if (i == '1' || i == '0')
            {
                count++;
            }
        }
    }
    return count;
}