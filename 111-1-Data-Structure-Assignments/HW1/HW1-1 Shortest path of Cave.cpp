#include <iostream>
using namespace std;

void push(char c);
void pop();
void print();
bool check(int i, int j);
void DFS(int i, int j);

int M;
int topIndex = -1;
char stack[1000];
int maze[100][100];
int used[100][100] = { 0 };

int main() {
    cin >> M;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            cin >> maze[i][j];
        }
    }
    DFS(0, 0);

    return 0;
}

void DFS(int i, int j) {
    if (check(i, j) == -1 || maze[i][j] == 0 || used[i][j] == 1) return;
    used[i][j] = 1;
    if (i == M - 1 && j == M - 1) {
        print();
        return;
    }

    push('N');
    DFS(i - 1, j);
    pop();
    push('E');
    DFS(i, j + 1);
    pop();
    push('S');
    DFS(i + 1, j);
    pop();
    push('W');
    DFS(i, j - 1);
    pop();
}

void push(char c) {
    stack[++topIndex] = c;
}
void pop() {
    topIndex--;
}
void print() {
    for (int i = 0; i <= topIndex; i++) {
        cout << stack[i];
    }
    cout << endl;
}
bool check(int i, int j) {
    if (i >= 0 && i < M && j >= 0 && j < M) return 1;
    return 0;
}