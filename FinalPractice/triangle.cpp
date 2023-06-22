#include <iostream>

using namespace std;

int pre[200000] = {0};

int main(void){
    int t; cin >> t;
    while(t--){
        int A, B, C, D; cin >> A >> B >> C >> D;
        for(int i = 0; i < 200000; i++) pre[i] = 0;
        long long int res = 0;
        for(int i = A; i <= B; i++){
            pre[i + B]++;
            pre[i + C + 1]--;
        }
        for(int i = 1; i <= B + C + 1; i++) pre[i] += pre[i - 1];
        /*for(int i = 1; i <= B + C + 1; i++) cout << pre[i] << " ";
        cout << "\n";*/
        for(int i = 1; i <= B + C + 1; i++) pre[i] += pre[i - 1];
        /*for(int i = 1; i <= B + C + 1; i++) cout << pre[i] << " ";
        cout << "\n";*/
        for(int i = C; i <= D && i <= B + C - 1; i++) res += pre[B + C + 1] - pre[i];
        cout << res << "\n";
    }
    return 0;
}