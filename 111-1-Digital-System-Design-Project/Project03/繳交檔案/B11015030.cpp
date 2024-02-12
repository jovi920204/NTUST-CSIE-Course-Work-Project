#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct Next {
    string next;
    string output;
};
struct Pair {
    string first;
    string second;
};
struct Cmp {
    bool operator () (string const &a, string const &b)const{
        if (a.size() != b.size()){
            return a.size() < b.size();
        }
        else {
            return a < b;
        }
    }
};
map<string, vector<Next>, Cmp> stateTable;
vector<vector<vector<Pair> > > implicationTable;
vector<vector<bool> > incompatible;
map<string, int> stateIndex;
vector<string> stateName;
vector<string> deletedStates;

void sieveIncompatible(int inputNum, int stateNum);
void listTransitionPair(int stateNum);
void checkTransitionPair(int stateNum, int inputNum);
void mergeCompatibleState(int stateNum, int inputNum);
string intToBinary(int x, int length);
void writeKiss(ofstream& kissOutputFile, int inputNum, int outputNum, int termNum, int stateNum, string resetState);
void writeDot(ofstream& dotOutputFile, int inputNum, int outputNum, int termNum, int stateNum, string resetState);
void writeInputDot(ofstream& dotInputFile, int inputNum, int outputNum, int termNum, int stateNum, string resetState);

int main(int argc, char *argv[]){
    ifstream inputFile;
    ofstream kissOutputFile;
    ofstream dotOutputFile;
    ofstream dotInputFile;
    inputFile.open(argv[1]);
    kissOutputFile.open(argv[2]);
    dotOutputFile.open(argv[3]);
    // dotInputFile.open(argv[4]);
    
    string resetState = "";
    int inputNum;
    int outputNum;
    int termNum;
    int stateNum;

    while(inputFile.good()){
        string type = ""; 
        string temp = "";
        inputFile >> type;
        if (type == ".start_kiss"){
            continue;
        }
        else if (type == ".i"){
            inputFile >> temp;
            inputNum = stoi(temp);
        }
        else if (type == ".o"){
            inputFile >> temp;
            outputNum = stoi(temp);
        }
        else if (type == ".p"){
            inputFile >> temp;
            termNum = stoi(temp);
        }
        else if (type == ".s"){
            inputFile >> temp;
            stateNum = stoi(temp);
        }
        else if (type == ".r"){
            inputFile >> resetState;
            string input;
            string currentState;
            string nextState;
            string output;
            for(int i = 0; i < termNum ; i++){
                inputFile >> input >> currentState >> nextState >> output;
                Next nextTemp;
                nextTemp.next = nextState;
                nextTemp.output = output;
                stateTable[currentState].push_back(nextTemp);
            }
            int index = 0;
            for (auto val : stateTable){
                stateIndex[val.first] = index;
                stateName.push_back(val.first);
                index++;
            }
        }
        else if (type == ".end_kiss"){
            continue;
        }
    }
    // writeInputDot(dotInputFile, inputNum, outputNum, termNum, stateNum, resetState);
    implicationTable = vector<vector<vector<Pair> > >(stateNum, vector<vector<Pair> >(stateNum));
    incompatible = vector<vector<bool> >(stateNum, vector<bool>(stateNum,0));
    sieveIncompatible(inputNum, stateNum);
    listTransitionPair(stateNum);
    checkTransitionPair(stateNum, inputNum);
    mergeCompatibleState(stateNum, inputNum);

    writeKiss(kissOutputFile, inputNum, outputNum, pow(2,inputNum)*(stateNum-deletedStates.size()), stateNum-deletedStates.size(), resetState);
    writeDot(dotOutputFile, inputNum, outputNum, pow(2,inputNum)*(stateNum-deletedStates.size()), stateNum-deletedStates.size(), resetState);
    return 0;
}

void sieveIncompatible(int inputNum, int stateNum){
    for (int i=0;i<stateTable.size();i++){
        incompatible[i][i] = 1;
    }
    for (int i=0;i<stateNum;i++){
        for (int j=0;j<stateNum;j++){
            int count = 0;
            for (int k=0;k<pow(2,inputNum);k++){
                if (stateTable[stateName[i]][k].output != stateTable[stateName[j]][k].output){
                    incompatible[i][j] = 1;
                    break;
                }
            }
        }
    }
}

void listTransitionPair(int stateNum){
    for (int i = 0; i < stateNum; i++){
        for (int j = 0; j < stateNum; j++){
            if (i == j || incompatible[i][j] == 1) continue;
            else{
                int inputNum = stateTable[stateName[i]].size();
                Pair pairTemp;
                vector<Pair> list;
                for (int k = 0; k < inputNum; k++){
                    pairTemp.first = stateTable[stateName[i]][k].next;
                    pairTemp.second = stateTable[stateName[j]][k].next;
                    list.push_back(pairTemp);
                }
                implicationTable[i][j] = list;
            }
        }
    }
}

void checkTransitionPair(int stateNum, int inputNum){
    for (int i = 0; i < stateNum; i++){
        for (int j = 0; j < stateNum; j++){
            if (incompatible[i][j] == 1) continue;
            string first, second;
            for (int k = 0; k < pow(2,inputNum); k++){
                first = implicationTable[i][j][k].first;
                second = implicationTable[i][j][k].second;
                if (first != second && incompatible[stateIndex[first]][stateIndex[second]] == 1){
                    incompatible[i][j] = 1;
                    checkTransitionPair(stateNum, inputNum);
                }
            }
        }
    }
}

void mergeCompatibleState(int stateNum, int inputNum){
    for (int i = 0; i < stateNum; i++){
        for (int j = 0; j < stateNum; j++){
            if (incompatible[i][j] == 0){
                string keepState = stateName[i];
                string deleteState = stateName[j];
                for (int k = 0; k < stateNum; k++){
                    incompatible[j][k] = 1;
                    incompatible[k][j] = 1;
                }
                for (auto& val : stateTable){               
                    for (auto& n : val.second){
                        if (n.next == deleteState){
                            n.next = keepState;
                        }
                    }
                }
                listTransitionPair(stateNum);
                auto it = find(deletedStates.begin(), deletedStates.end(), deleteState);
                if (it == deletedStates.end()) deletedStates.push_back(deleteState); 
            }
        }
    }
}

void writeKiss(ofstream& kissOutputFile, int inputNum, int outputNum, int termNum, int stateNum, string resetState){
    kissOutputFile << ".start_kiss\n";
    kissOutputFile << ".i " << inputNum << "\n";
    kissOutputFile << ".o " << outputNum << "\n";
    kissOutputFile << ".p " << termNum << "\n";
    kissOutputFile << ".s " << stateNum << "\n";
    kissOutputFile << ".r " << resetState << "\n";
    for (auto val : stateTable){
        string curr = val.first;
        auto it = find(deletedStates.begin(), deletedStates.end(), curr);
        if (it != deletedStates.end()) continue;
        for (int i = 0; i < val.second.size(); i++){
            kissOutputFile << intToBinary(i, inputNum) << " " << curr << " " << val.second[i].next << " " << val.second[i].output << "\n";
        }
    }
    kissOutputFile << ".end_kiss";
}

void writeDot(ofstream& dotOutputFile, int inputNum, int outputNum, int termNum, int stateNum, string resetState){
    vector<string> state;
    for (auto val : stateTable){
        string curr = val.first;
        auto it = find(deletedStates.begin(), deletedStates.end(), curr);
        if (it != deletedStates.end()) continue;
        state.push_back(curr);
    }
    
    dotOutputFile << "digraph STG {\n";
    dotOutputFile << "  " << "rankdir=LR;\n\n";
    dotOutputFile << "  " << "INIT [shape=point];\n";
    for (auto val : state){
        dotOutputFile << "  " << val << " [label=\"" << val << "\"];\n";
    }
    dotOutputFile << "\n";
    dotOutputFile << "  " << "INIT -> " << resetState << ";\n";
    for (auto val : stateTable){
        string curr = val.first;
        auto it = find(deletedStates.begin(), deletedStates.end(), curr);
        if (it != deletedStates.end()) continue;
        for (int i = 0; i < val.second.size(); i++){
            dotOutputFile << "  " << curr << " -> " << val.second[i].next << " [label=\"" << intToBinary(i, inputNum) << "/" << val.second[i].output << "\"];\n";
        }
    }
    dotOutputFile << "}\n";
}

void writeInputDot(ofstream& dotInputFile, int inputNum, int outputNum, int termNum, int stateNum, string resetState){
    vector<string> state;
    for (auto val : stateTable){
        string curr = val.first;
        state.push_back(curr);
    }
    
    dotInputFile << "digraph STG {\n";
    dotInputFile << "  " << "rankdir=LR;\n\n";
    dotInputFile << "  " << "INIT [shape=point];\n";
    for (auto val : state){
        dotInputFile << "  " << val << " [label=\"" << val << "\"];\n";
    }
    dotInputFile << "\n";
    dotInputFile << "  " << "INIT -> " << resetState << ";\n";
    for (auto val : stateTable){
        string curr = val.first;
        for (int i = 0; i < val.second.size(); i++){
            dotInputFile << "  " << curr << " -> " << val.second[i].next << " [label=\"" << intToBinary(i, inputNum) << "/" << val.second[i].output << "\"];\n";
        }
    }
    dotInputFile << "}\n";
}
string intToBinary(int x, int length){
    string ret = "";
    for (int i=0;i<length;i++){
        ret += to_string(x%2);
        x/=2;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}