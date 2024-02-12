#include <iostream>
#include <regex> // using regex
#include <vector> // using vector
#include <utility> // using pair
#include <algorithm> // using sort
#include <ctime> // using time
#include <time.h> // using for determine performance
#include <queue> // using for priority_queue

using namespace std;

void printHourMin(int time);
string randomSchedule();

struct task{
    int start;
    int end;
    int index;
};

// define a priority_queue comparision function, 
// arrange in ascending order based on the latest end time of each classroom.
struct cmp {
    bool operator() (const vector<task>& a, const vector<task>& b) const {
        return a.back().end > b.back().end;
    }
};

// define a sort comparision function, 
// arrange in ascending order based on the start time.
bool sort_cmp(const task& a, const task& b)
{
    return a.start < b.start;
}

int main(){
    srand(time(NULL));
    double START, END;
    vector<string> data;

    // Random input  
    int n;
    cout << "How many lecture you have? => "; 
    cin >> n;
    for (int i=1;i<=n;i++){
        string input = "Lecture " + to_string(i) + ":  ";
        input += randomSchedule();
        cout << input << endl;
        data.push_back(input);
    }

    // Manual input
    /*
    string input;
    while(getline(cin, input)){
        data.push_back(input);
    }
    */
    // Store input data in a computable format
    vector<task> tasks;
    const regex regex(
        "^(?:Lecture \\d+: +)(\\d{1,2}):(\\d{2})-(\\d{1,2}):(\\d{2})$"
        );

    for (int i=0;i<data.size();i++) {
        std::smatch match;
        // using regex formatted the input data to computable starting time and ending time
        if (regex_match(data[i], match, regex)) {
            const int start_hour = std::stoi(match[1]);
            const int start_minute = std::stoi(match[2]);
            const int end_hour = std::stoi(match[3]);
            const int end_minute = std::stoi(match[4]);
            int start = start_hour*60+start_minute;
            int end = end_hour*60+end_minute;

            // store input in tasks
            task new_task;
            new_task.start = start;
            new_task.end = end;
            new_task.index = i+1;
            tasks.push_back(new_task);
        }
    }

    START = clock();

    // Sort intervals in ascending order of thier staring time with sort algorithm in C++
    sort(tasks.begin(), tasks.end(), sort_cmp);

    // Initialze the classroom
    priority_queue<vector<task>, vector<vector<task> >, cmp> pq;
    // assign each class to classroom
    for (int i=0;i<tasks.size();i++){
        // if number of room is empty, or there didn't have compitable room for current class,
        if (pq.empty() || pq.top().back().end > tasks[i].start){
            // then give a new room for current class.
            vector<task> new_room;
            new_room.push_back(tasks[i]);
            pq.push(new_room);
        }
        // else, which means there have compitable room for current class,
        else{
            // then assign the class to the room
            vector<task> cur_room = pq.top();
            cur_room.push_back(tasks[i]);
            pq.pop();
            pq.push(cur_room);
        }
    }

    END = clock();

    // Output results
    cout << "----------" << endl;
    cout << "The consume time = " << (END - START) << endl;
    cout << "The minimum number of classrooms = " << pq.size() << endl;
    cout << "----------" << endl;
    // Output classroom schedule
    /*
    while(!pq.empty()){
        for (auto p : pq.top()){
            cout << "Lecture: " << p.index << " ";
            cout << "(";
            printHourMin(p.start);
            cout << ", ";
            printHourMin(p.end);
            cout << ") ";
        }
        cout << endl;
        pq.pop();
    }
    */
    return 0;
}

void printHourMin(int time){
    int hour = time/60;
    int min = time%60;
    cout << hour << ":";
    if (min == 0){
        cout << "00";
    }
    else{
        cout << min;
    }
}

string randomSchedule(){
    // assume the time of class is during 9 AM to 5 PM
    
    int num1 = rand() % 9 + 8; // generate first number
    int num2 = rand() % 9 + 9; // generate second number

    // make sure the distance between first and second must larger than or equal to one.
    while (abs(num1 - num2) < 1) {
        num2 = rand() % 9 + 9; // if distance less than one, regenerate second number.
    }
    if (num1 > num2){
        swap(num1, num2);
    }
    // based on random number, assign them to there class is on the hour or half the hour.
    // and return the result.
    if (abs(num1 - num2) == 1){
        bool flag = rand() % 2;
        if (flag == 0){
            return to_string(num1)+":00-" + to_string(num2) + ":00";
        }
        else{
            return to_string(num1)+":30-" + to_string(num2) + ":30";
        }
    }
    else{
        bool flag1 = rand() % 2;
        bool flag2 = rand() % 2;
        if (flag1 == 0 && flag2 == 0){
            return to_string(num1)+":00-" + to_string(num2) + ":00";
        }
        if (flag1 == 0 && flag2 == 1){
            return to_string(num1)+":00-" + to_string(num2) + ":30";
        }
        if (flag1 == 1 && flag2 == 0){
            return to_string(num1)+":30-" + to_string(num2) + ":00";
        }
        if (flag1 == 1 && flag2 == 1){
            return to_string(num1)+":30-" + to_string(num2) + ":30";
        }
    }
}