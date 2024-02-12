#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<vector<string>> table = {
{
	{" _ "},
	{"| |"},
	{"|_|"},
},
{
	{"   "},
	{"  |"},
	{"  |"},
},
{
	{" _ "},
	{" _|"},
	{"|_ "},
},
{
	{" _ "},
	{" _|"},
	{" _|"},
},
{
	{"   "},
	{"|_|"},
	{"  |"},
},
{
	{" _ "},
	{"|_ "},
	{" _|"},
},
{
	{" _ "},
	{"|_ "},
	{"|_|"},
},
{
	{" _ "},
	{"  |"},
	{"  |"},
},
{
	{" _ "},
	{"|_|"},
	{"|_|"},
},
{
	{" _ "},
	{"|_|"},
	{" _|"},
},
};
int main(){
	string input;
	while (getline(cin, input)) {
		vector < vector<string>> ans(3, vector<string>());
		for (int i = 0; i < 3; i++) {
			for (const auto& val : input) {
				if ('9' >= val && val >= '0') {
					ans[i].push_back(table[val - '0'][i]);
				}
			}
		}
		for (const auto& val : ans) {
			for (const auto& val2 : val) {
				cout << val2 ;
			}
			cout << "\n";
		}
	}
	return 0;
}