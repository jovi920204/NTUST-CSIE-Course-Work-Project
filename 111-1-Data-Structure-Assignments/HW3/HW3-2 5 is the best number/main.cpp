#include <iostream>
#include <vector>
#include <string>
using namespace std;

void bubble_sort(vector<int> data);
void insertion_sort(vector<int> data);
void selection_sort(vector<int> data);
void sorted(vector<int> data);

int main(){
    vector<int> data;
    int temp;
    while(cin >> temp){
        data.push_back(temp);
    }
    bubble_sort(data);
    insertion_sort(data);
    selection_sort(data);
    sorted(data);
    return 0;
}
// 21 24 28 15 20 19 30 41 20 28 13 12 33 25 7
// 39 9 45 63 18 81 108 54 72 36
void bubble_sort(vector<int> data){
    int a, b;
    int count = 0;
    for(int i=0;i<data.size();i++){
        for (int j=0;j<data.size()-i-1;j++){
            if (data[j] > data[j+1]){
                count++;
                int temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
                a = data[j];
                b = data[j+1];
            }
            if (count == 5){
                break;
            }
        }
        if (count == 5){
            break;
        }
    }
    cout << "Bubble: " << a << ", " << b << "; ";
    for (int i=0;i<data.size()-1;i++){
        cout << data[i] << " ";
    }
    cout << data[data.size()-1] << endl;
}

void insertion_sort(vector<int> data){
    int count = 1; // data[0] was insert in index 0
    for (int i=1;i<data.size();i++){
        int temp = data[i];
        int j = i-1;
        while(temp <= data[j] && j >= 0){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = temp;
        count++;
        if (count == 5) break;
    }
    cout << "Insertion: ";
    for (int i=0;i<data.size()-1;i++){
        cout << data[i] << " ";
    }
    cout << data[data.size()-1] << endl;
}

void selection_sort(vector<int> data){
    int count = 0;
    for (int i=0;i<data.size();i++){
        int small = data[i];
        int pos = i;
        for (int j=0+i;j<data.size();j++){
            if (small > data[j]){
                small = data[j];
                pos = j;
            }    
        }
        int temp = data[i];
        data[i] = data[pos];
        data[pos] = temp;
        count++;
        if (count == 5){
            cout << "Selection: " << small << "; ";
            for (int i=0;i<data.size()-1;i++){
                cout << data[i] << " ";
            }
            cout << data[data.size()-1] << endl;
        }
    }
}

void sorted(vector<int> data){
    for (int i=1;i<data.size();i++){
        int temp = data[i];
        int j = i-1;
        while(temp <= data[j] && j >= 0){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = temp;
    }
    for (int i=0;i<data.size()-1;i++){
        cout << data[i] << " ";
    }
    cout << data[data.size()-1];
}