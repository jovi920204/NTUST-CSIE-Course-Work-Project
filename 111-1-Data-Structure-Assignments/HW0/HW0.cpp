#include <iostream>
using namespace std;

int main()
{
    int fib[46] = {0,1,1};
    for (int i = 3; i <= 45; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    int N;
    cin >> N;
    while (N--) {
        int num;
        cin >> num;
        cout << fib[num] << endl;
    }
    return 0;
}
