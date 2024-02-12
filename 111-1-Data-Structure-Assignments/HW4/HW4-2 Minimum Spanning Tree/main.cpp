#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Edge{
    int v1;
    int v2;
    int weight;
};

int vertexNum;
int edgeNum;
vector<vector<int> > graph;
bool isFinished(vector<int>& visited, int vertexNum);
void sorted(vector<Edge>& MST);
void swapEdge(Edge& e1, Edge& e2);

int main() {
    cin >> vertexNum >> edgeNum;
    graph.resize(vertexNum, vector<int>(vertexNum, 0));
    bool alphaFlag = 0;
    for (int i = 0; i < edgeNum; i++) {
        char startNode, endNode;
        int weight;
        cin >> startNode >> endNode >> weight;
        if (isdigit(startNode)) {
            alphaFlag = false;
            graph[atoi(&startNode)][atoi(&endNode)] = weight;
            graph[atoi(&endNode)][atoi(&startNode)] = weight;
        }
        else {
            alphaFlag = true;
            graph[startNode - 'A'][endNode - 'A'] = weight;
            graph[endNode - 'A'][startNode - 'A'] = weight;
        }
    }
    vector<int> predecessor(vertexNum,-1);
    vector<int> key(vertexNum, 10000000000);
    vector<int> visited(vertexNum,0);
    int currNode = 0;
    key[currNode] = 0;
    while (!isFinished(visited, vertexNum)) {
        visited[currNode] = 1;
        for (int i = 0; i < graph[currNode].size(); i++) {
            if (graph[currNode][i] == 0) {
                continue;
            }
            else {
                if (visited[i] == 0 && key[i] > graph[currNode][i]) {
                    predecessor[i] = currNode;
                    key[i] = graph[currNode][i];
                }
            }
        }
        int minLength = 10000000000;
        int nextNode = currNode;
        for (int i = 0; i < vertexNum; i++) {
             if (visited[i] == 0){
                if (minLength > key[i]) {
                    minLength = key[i];
                    nextNode = i;
                }
            }
        }
        currNode = nextNode;
    }
    int totalWeight = 0;
    vector<Edge> MST;
    for (int i=1;i<vertexNum;i++){
        Edge temp;
        if (i < predecessor[i]) {
            temp.v1 = i;
            temp.v2 = predecessor[i];
        }
        else {
            temp.v2 = i;
            temp.v1 = predecessor[i];
        }
        temp.weight = key[i];
        totalWeight += key[i];
        MST.push_back(temp);
    }
    cout << totalWeight << endl;
    sorted(MST);
    for (int i=0;i<MST.size();i++){
        if (alphaFlag == 1){
            cout << (char)(MST[i].v1+'A') << " " << (char)(MST[i].v2+'A') << " " << MST[i].weight;
        }
        else{
            cout << MST[i].v1 << " " << MST[i].v2 << " " << MST[i].weight;
        }
        if (i < MST.size()-1) cout << endl;
    }
    return 0;
}

bool isFinished(vector<int>& visited, int vertexNum) {
    // cout << "Q" << endl;
    for (int i = 0; i < vertexNum; i++) {
        if (visited[i] == 0) {
            return 0;
        }
    }
    return 1;
}

void sorted(vector<Edge>& MST){
    for (int i=0;i<MST.size()-1;i++){
        for (int j=0;j<MST.size()-i-1;j++){
            if (MST[j].weight > MST[j+1].weight){
                swapEdge(MST[j], MST[j+1]);
            }
            if (MST[j].weight == MST[j+1].weight && MST[j].v1 > MST[j+1].v1){
                swapEdge(MST[j], MST[j+1]);
            }
            if (MST[j].weight == MST[j+1].weight && MST[j].v1 == MST[j+1].v1 && MST[j].v2 > MST[j+1].v2){
                swapEdge(MST[j], MST[j+1]);
            }
        }
    }
}

void swapEdge(Edge& e1, Edge& e2){
    Edge t = e1;
    e1 = e2;
    e2 = t;
}