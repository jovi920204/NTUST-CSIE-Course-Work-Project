#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Info {
	string name;
	int arriveTime;
	int timeLeft;
};

class Queue
{
public:
	void push(string name, int startTime, int timeLeft); // timeLeft = remaining time 
	Info &front();
	Info &pop();
	void print();
	int size();
	bool isEmpty();

private:
	int frontIndex = -1;
	vector<Info> info;
};

void Queue::push(string name, int arriveTime, int timeLeft)
{
	if (frontIndex == -1) {
		frontIndex++;
	}
	Info i;
	i.name = name;
	i.arriveTime = arriveTime;
	i.timeLeft = timeLeft;
	info.push_back(i);
}
Info &Queue::front()
{
	return info[frontIndex];
}
Info &Queue::pop()
{
	Info ret = info[frontIndex];
	frontIndex++;
	return ret;
}
void Queue::print()
{
	for (int i = frontIndex; i < info.size(); i++) {
		cout << info[i].name << " " << info[i].arriveTime << " " << info[i].timeLeft << endl;
	}
}

int Queue::size()
{
	if (frontIndex == -1) return 0;
	return info.size() - frontIndex;
}

bool Queue::isEmpty()
{
	if (frontIndex == -1 || frontIndex == info.size()) return true;
	else return false;
}

bool counterIsEmpty(vector<Queue>& counter);
int minPeopleCounter(vector<Queue>& counter); // return the counter ID, which have less people get in line.
void printCounter(vector<Queue>& counter); // Print all counter information
int minDiffTime(vector<Queue>& counter, Queue& q, int now);
void printAll(vector<Queue>& counter, Queue& q, int now);
void rumTime(vector<Queue>& counter, int diff); 
void recordPeopleLeft(vector<Queue>& counter, vector<string>& record, int now);
void printRecord(vector<string>& record);

int n; // number of counters
vector<Queue> counter;
vector<string> record;
Queue q;
int main() {
	cin >> n;
	counter.resize(n);
	string name;
	int arriveTime;
	int durationTime;
	while (cin >> name) {
		cin >> arriveTime >> durationTime;
		q.push(name, arriveTime, durationTime);
	}

	int time = 0;
	while (!q.isEmpty() || !counterIsEmpty(counter)) {
		int minDiff = minDiffTime(counter, q, time);
		time += minDiff;
		rumTime(counter, minDiff);
		recordPeopleLeft(counter, record, time);
		if (!q.isEmpty() && q.front().arriveTime == time) {
			counter[minPeopleCounter(counter)].push(q.front().name, q.front().arriveTime, q.front().timeLeft);
			q.pop();
		}
		//cout << "minDiff : " << minDiff << endl;
		//printAll(counter, q, time);
	}
	printRecord(record);
}

// q.front().name, q.front().arriveTime, q.front().timeLeft
bool counterIsEmpty(vector<Queue>& counter) {
	for (auto val : counter) {
		if (!val.isEmpty()) {
			return 0;
		}
	}
	return 1;
}

int minPeopleCounter(vector<Queue>& counter) { // Return counter ID;
	int minSize = 1000000;
	int loc = 0;
	for (int i = 0; i < counter.size();i++) {
		if (minSize > counter[i].size()) {
			minSize = counter[i].size();
			loc = i;
		}
	}
	return loc;
}

int minDiffTime(vector<Queue>& counter, Queue& q, int now) {
	int minDiff = 1000000;
	if (!q.isEmpty()) minDiff = q.front().arriveTime - now;
	
	for (int i = 0; i < counter.size();i++) {
		if (!counter[i].isEmpty()) {
			if (minDiff > counter[i].front().timeLeft) {
				minDiff = counter[i].front().timeLeft;
			}
		}
	}
	return minDiff;
}

void printCounter(vector<Queue>& counter) {
	for (int i = 0; i < counter.size(); i++) {
		cout << "ID = " << i << endl;
		counter[i].print();
	}
}

void printAll(vector<Queue>& counter, Queue& q, int now) {
	cout << "-----------" << endl;
	cout << "Time : " << now << endl;
	cout << "Queue : " << endl;
	if (!q.isEmpty()) q.print();
	else cout << "Empty" << endl;
	for (int i = 0; i < counter.size(); i++) {
		cout << endl;
		cout << "Counter ID " << i << " : " << endl;
		if (!counter[i].isEmpty()) {
			counter[i].print();
		}
		else {
			cout << "Empty" << endl;
		}
	}
	cout << "-----------" << endl;
}

// Cost the timeLeft in every people in counter, when time move to next period
void rumTime(vector<Queue>& counter, int diff) { 
	for (int i = 0; i < counter.size(); i++) {
		if (!counter[i].isEmpty()) {
			counter[i].front().timeLeft -= diff;
			//cout << counter[i].front().name << " " << counter[i].front().timeLeft << endl;
		}
	}
}

void recordPeopleLeft(vector<Queue>& counter, vector<string>& record, int now) {
	for (int i = 0; i < counter.size(); i++) {
		if (!counter[i].isEmpty()) {
			if (counter[i].front().timeLeft == 0) {
				string output = counter[i].front().name + " " + to_string(now) + " " + to_string(i);
				record.push_back(output);
				counter[i].pop();
			}
			
		}
	}
}

void printRecord(vector<string>& record) {
	for (auto val : record) {
		cout << val << endl;
	}
}