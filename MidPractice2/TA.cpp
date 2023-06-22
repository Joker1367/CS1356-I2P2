#include <iostream>
#define MOD 1000000007

using namespace std;

int main(void){
    int t;
    cin >> t;
    while(t--){
        long long int x;
        string str;
        cin >> x >> str;
        long long int len = str.size();
        for(int i = 0; i < x; i++){
            int time = str[i] - '1';
            long long int inc = (len - i - 1 + MOD) % MOD; // 注意這裡要確保inc是正的
            if(str.size() < 1000000){
                string substring = str.substr(i + 1, inc);
                for(int i = 0; i < time; i++){
                    if(str.size() >= 1000000) break;
                    str.append(substring);
                }  
            }
            len = (len + time * inc) % MOD;
        }
        cout << len << "\n";
    }
    return 0;
}