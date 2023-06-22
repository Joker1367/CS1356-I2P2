#include <iostream>

using namespace std;

int table[200001];

int main(void){
    int t; cin >> t;
    while(t--){
        int n, target; cin >> n >> target;
        for(int i = 1; i <= n; i++) cin >> table[i];
        int l = 1; int r = n + 1; //確保能算到喝n天
        int res = -1;
        while(l < r){
            int mid = (l + r) / 2;
            long long int tmp_target = 0;
            bool find = false;
            for(int i = 1, dec = 0; i <= n && !find; i += mid, dec++){
                for(int j = 0; j < mid && i + j <= n; j++){
                    tmp_target += ((table[i + j] - dec) > 0) ? (table[i + j] - dec) : 0;
                    if(tmp_target >= target){
                        res = mid;
                        find = true;
                        break;
                    }
                }
            }
            if(find) r = mid;
            else l = mid + 1;
        }
        cout << res << "\n";
    }
    return 0;
}