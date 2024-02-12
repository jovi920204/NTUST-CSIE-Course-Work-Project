#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Queue {
private:
    vector<int> data;

public:
    int front() {
        return this->data[0];
    }
    void push(int x) {
        data.push_back(x);
    };
    void pop() {
        vector<int> temp = data;
        data.clear();
        data.assign(temp.begin() + 1, temp.end());
    };
    bool empty() {
        return data.empty();
    };
};

bool checkCycle(int sourceNode);


vector<vector<int> > graph;
int nodeNumber;

int main(){
    cin >> nodeNumber;
    graph.resize(nodeNumber, vector<int>());
    int startNode, endNode;
    while(cin >> startNode >> endNode){
        graph[startNode].push_back(endNode);
    }
    for (int i=0;i<nodeNumber;i++){
        if (checkCycle(i)){
            cout << "Cycle";
            return 0;
        }
    }
    cout << "No Cycle";
    return 0;
}

bool checkCycle(int sourceNode){
    vector<bool> used(nodeNumber,false);
    used[sourceNode] = true;
    Queue q;
    q.push(sourceNode);
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        for (int i=0;i<graph[curr].size();i++){
            if (graph[curr][i] == sourceNode){
                return 1;
            }
            if (used[graph[curr][i]] == false){
                used[graph[curr][i]] = true;
                q.push(graph[curr][i]);
            }
        }
    }
    return 0;
}