#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

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

int main(){
    map<string, int, Cmp> mp;
    mp["s1"] = 0;
    mp["s2"] = 1;
    mp["s10"] = 2;
    for (auto val : mp){
        cout << val.first << endl;
    }
}

