// Name: ±i∫Õ≈Ô
// Date: April, 2 , 2022  
// Last Update: April, 2 , 2022  
// Problem statement: Shisensho

#include <iostream>
#include <vector>
#include <stack>

using namespace std;
struct Pos {
	int x, y;
};

vector<vector <int>> board(8, vector<int>(8));
void dfs(int x, int y, int x_des, int y_des);
bool reach = false;
vector <vector <bool> > visited(8, vector<bool>(8));
vector <vector <bool> > turn(8, vector<bool>(8));
stack<Pos> stk;
int main() {
	
	
	for (int i = 1; i < 7; i++) {
		for (int j = 1; j < 7; j++) {
			cin >> board[i][j];
		}
	}
	int x1, y1, x2, y2;
	int count = 18;
	while (count) {
		visited.clear();
		visited.resize(8, vector<bool>(8));
		cin >> y1 >> x1 >> y2 >> x2;
		x1 += 1;
		y1 += 1;
		x2 += 1;
		y2 += 1;
		if (board[x1][y1] != board[x2][y2]) {
			cout << "bad pair" << endl;
			continue;
		}
		dfs(x1, y1, x2, y2);
		if (reach == 1) {
			count--;
			cout << "pair matched" << endl;
			board[x1][y1] = 0;
			board[x2][y2] = 0;
		}
		else {
			cout << "bad pair" << endl;
		}
		/*for (auto val1 : visited) {
			for (auto val2 : val1) {
				cout << val2 << " ";
			}
			cout << endl;
		}*/
	}
	
	return 0;
}
void dfs(int x, int y, int x_des, int y_des) {
	//cout << "dfs" << endl;
	//cout << x << ", " << y << " | " << x_des << ", " << y_des << endl;
	//cout << stk.top().x << ", " << stk.top().y << endl;
	if (x == x_des && y == y_des) {
		reach = 1;
		return;
	}
	if (visited[x][y] == 1) {
		return;
	}
	if (!stk.empty()) {
		stk.pop();
	}
	
	visited[x][y] = 1;
	// 4 direction
	Pos temp;
	//cout << "≠» " << board[x][y] << " " << board[x_des][y_des] << endl;
	if ((x-1 >= 0) && ((board[x - 1][y] == 0 && visited[x - 1][y] == 0) || (x-1 == x_des && y == y_des))) {
		temp.x = x - 1;
		temp.y = y;
		stk.push(temp);
	}
	if ((x+1 <= 7) &&((board[x + 1][y] == 0 && visited[x + 1][y] == 0) || (x + 1 == x_des && y == y_des))) {
		temp.x = x + 1;
		temp.y = y;
		stk.push(temp);
	}
	if ((y-1 >= 0) &&((x == x_des && y-1 == y_des) || (board[x][y - 1] == 0 && visited[x][y - 1] == 0))) {
		temp.x = x;
		temp.y = y - 1;
		stk.push(temp);
	}
	if ((y + 1 <= 7) && ((board[x][y + 1] == 0 && visited[x][y + 1] == 0) || (x == x_des && y + 1 == y_des))) {
		temp.x = x;
		temp.y = y + 1;
		stk.push(temp);
	}
	if (stk.empty()) {
		return;
		// no way can go
	}
	//cout << "Æyº– " << stk.top().x << " , " << stk.top().y << endl;
	dfs(stk.top().x, stk.top().y, x_des, y_des);
}


/*
9 2 4 0 9 7
6 9 0 0 1 5
5 3 3 0 2 2
3 4 7 0 9 5
4 6 8 0 2 6
6 5 1 4 3 8
2 4 5 5

9 2 4 8 9 7
6 9 1 7 1 5
5 3 3 7 2 2
3 4 7 1 9 5
4 6 8 8 2 6
6 5 1 4 3 8
3 1 3 2


*/