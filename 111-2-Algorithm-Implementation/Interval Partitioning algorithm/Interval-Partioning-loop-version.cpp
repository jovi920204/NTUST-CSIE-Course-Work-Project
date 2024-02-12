#include <iostream>
#include <regex> // using regex
#include <vector> // using vector
#include <utility> // using pair
#include <algorithm> // using sort
#include <ctime> // using time
#include <time.h> // using for determine performance

using namespace std;

void printHourMin(int time);
string randomSchedule();
bool cmp(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
    return a.first < b.first;
}

int main() {
    // Initialize random seed, which can be set to the current time
    srand(time(NULL)); 
    double START, END;
    
    // Generate random test data
    int n;
    cout << "How many lecture you have? => ";
    cin >> n;
    // cout << "There is random lecture schedule" << endl;
    vector<string> data;
    for (int i=1;i<=n;i++){
        string input = "Lecture " + to_string(i) + ":  ";
        input += randomSchedule();
        // cout << input << endl;
        data.push_back(input);
    }
    
    // Store input data in a computable format
    vector<pair<int,int> > tasks;
    const regex regex(
        "^(?:Lecture \\d+: +)(\\d{1,2}):(\\d{2})-(\\d{1,2}):(\\d{2})$"
        );

    for (int i=0;i<data.size();i++) {
        std::smatch match;
        if (regex_match(data[i], match, regex)) {
            const int start_hour = std::stoi(match[1]);
            const int start_minute = std::stoi(match[2]);
            const int end_hour = std::stoi(match[3]);
            const int end_minute = std::stoi(match[4]);

            int start = start_hour*60+start_minute;
            int end = end_hour*60+end_minute;
            tasks.push_back(make_pair(start, end));
        }
    }

    START = clock();

    // Sort intervals in ascending order of thier staring time with sort algorithm in C++
    sort(tasks.begin(), tasks.end(), cmp);

    // Initialze the classroom
    vector<vector<pair<int, int> > > rooms;
    vector<pair<int, int> > room;
    room.push_back(tasks[0]);
    rooms.push_back(room);

    // Traversing each tasks  
    for (int i=1;i<tasks.size();i++){
        bool assigned = false;
        // if the task in current time doesn't overlap other previous task, then add to the exist classroom
        for (int j=0;j<rooms.size();j++){
            pair<int, int> lask_task = rooms[j].back(); 
            if (tasks[i].first >= lask_task.second){
                rooms[j].push_back(tasks[i]);
                assigned = true;
                break;
            }
        }
        // if don't have avaliable existed room can assigned, then create new room for this task
        if (!assigned){
            vector<pair<int, int> > new_room;
            new_room.push_back(tasks[i]);
            rooms.push_back(new_room);
        }
        
    }
    
    END = clock();

    // Output results
    cout << "The consume time = " << (END - START) / CLOCKS_PER_SEC << endl;
    cout << "The minimum number of classrooms = " << rooms.size() << endl;
    
    // If tou want to output schedule, you can remove the comment below.
    /*
    for (int i=0;i<rooms.size();i++){
        for (int j=0;j<rooms[i].size();j++){
            cout << "(";
            printHourMin(rooms[i][j].first);
            cout << ", ";
            printHourMin(rooms[i][j].second);
            cout << ") ";
        }
        cout << endl;
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
    
    int num1 = rand() % 9 + 8; // 生成第一個數字
    int num2 = rand() % 9 + 9; // 生成第二個數字

    // 確保兩個數字的差距大於等於 1
    while (abs(num1 - num2) < 1) {
        num2 = rand() % 9 + 9; // 如果差距不足 1，重新生成第二個數字
    }
    if (num1 > num2){
        swap(num1, num2);
    }
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