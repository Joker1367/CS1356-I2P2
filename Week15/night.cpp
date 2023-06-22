#include <iostream>

using namespace std;

int que[5000];

int main(void){
    int t; cin >> t;
    while(t--){
        int n, m, k; cin >> n >> m >> k;
        for(int i = 0; i < n; i++) cin >> que[i];
        int res = 0;
        if(k < m){
            for(int i = 0; i <= k; i++){
                int least = 1000000000;
                for(int j = 0; j <= m - 1 - k; j++){
                    least = min(max(que[i + j], que[i + j + n - m]), least);
                }
                res = max(res, least);
            }
        }
        else{
            for(int i = 0; i <= m - 1 ; i++) res = max(res, max(que[0 + i], que[n - m + i]));
        }
        cout << res << "\n";
    }
    return 0;
}