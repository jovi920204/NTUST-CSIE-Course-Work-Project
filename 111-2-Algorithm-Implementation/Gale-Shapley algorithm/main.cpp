#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <random>
#include <time.h>   
using namespace std;

vector<vector<int> > randomPreferenceList(int n);
int main(){
    srand( time(NULL) );
    int m,w; // m for man, n for woman
    cout << "input number of males/females (number of males and females are equal) => ";
    cin >> m; 
    w = m;
    vector<vector<int> > manPreference(m+1,vector<int>(w+1));
    vector<vector<int> > womanPreference(w+1,vector<int>(m+1));
    vector<vector<int> > womanRanking(w+1, vector<int>(m+1)); 
    manPreference = randomPreferenceList(m);
    womanPreference = randomPreferenceList(w);

    // Print Man and Woman Preference Lists
    /*
    for (auto val1 : manPreference){
        for (auto val2 : val1){
            cout << val2 << " ";
        }
        cout << endl;
    }
    for (auto val1 : womanPreference){
        for (auto val2 : val1){
            cout << val2 << " ";
        }
        cout << endl;
    }
    */

    // Manual Input
    /*
    cout << "input sequencly the priority of male's preference" << endl;
    for (int i=1;i<=m;i++){
        for (int j=1;j<=w;j++){
            cin >> manPreference[i][j];
        }
    }
    cout << "input sequencly the priority of female's preference" << endl;
    for (int i=1;i<=w;i++){
        for (int j=1;j<=m;j++){
            cin >> womanPreference[i][j];
        }
    }
    */
   
    double START,END; 
    START = clock(); // the START of the algorithm

    // construct the woman's ranking (man is the index)
    for (int i=1;i<=w;i++){
        for (int j=1;j<=m;j++){
            int man = womanPreference[i][j];
            int ranking = j;
            womanRanking[i][man] = ranking; 
        }
    }
    vector<int> Next(m+1, 1); // Record the next woman a man proposes to.
    vector<int> Current(w+1,0); // Record the currently engaged man.
    
    // Initialize each person to be free
    queue<int> freeMan;
    for (int i=1;i<=m;i++){
        freeMan.push(i);
    }

    while(!freeMan.empty()){
        int man = freeMan.front(); // free man
        int woman = manPreference[man][Next[man]++]; // ready to be proposed
        // cout << man << " " << woman << endl;
        if (Current[woman] == 0){ // if woman is free
            Current[woman] = man;
            freeMan.pop();
        }
        else if(womanRanking[woman][man] < womanRanking[woman][Current[woman]]){ // woman prefers man to her fiance
            freeMan.pop(); 
            freeMan.push(Current[woman]); // m' become free
            Current[woman] = man; // woman and man become engaged
        }
    }
    END = clock(); // the end of the algorithm
    // Return Engaged Lists
    /*
    cout <<"Woman, Man" << endl; 
    for (int i=1;i<=w;i++){
        cout << i << " " << Current[i] << endl;
    }
    */

    // Print Time Consume
    cout << "------ Time Consume ------" << endl;
    cout << (END - START) << " ms" << endl;
    cout <<  "------*-----------*------" << endl;
    return 0;
}

vector<vector<int> > randomPreferenceList(int n){
    vector<vector<int> > retList(n+1, vector<int>(n+1));
    
    int min = 1;
    int max = n;
    /* generrate the random number, range is [min , max] */
    for (int i=1;i<=n;i++){
        set<int> exist;
        // counter
        int counter = 1;
        while(counter <= n){
            // random number between 1 to n
            int randomNumber = rand() % (max - min + 1) + min;
            if (exist.count(randomNumber) == 0){
                exist.insert(randomNumber);
                retList[i][counter] = randomNumber;
                counter++;
            }
            
        }
    }
    return retList;
}