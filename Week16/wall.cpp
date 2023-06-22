#include <iostream>
#include <vector>

using namespace std;

int main(void){
    int t; cin >> t;
    while(t--){
        int n, q; cin >> n >> q;
        int section[n + 1] = {0};
        int cum[n + 1] = {0};
        vector<pair<int, int>> soldier;
        for(int i = 0; i < q; i++){
            int l, r; cin >> l >> r;
            soldier.push_back({l, r});
            for(int j = l; j <= r; j++) section[j]++;
        }
        int res = 0;
        for(int i = 0; i < q; i++){
            int dec = 10000; 
            int left = soldier[i].first; int right = soldier[i].second; int tmp_res = 0;
            for(int j = left; j <= right; j++) section[j]--;
            for(int j = 1; j <= n; j++){
                if(section[j] > 0) tmp_res++;
                if(section[j] == 1) cum[j] = cum[j - 1] + 1;
                else cum[j] = cum[j - 1];
            }
            for(int j = i + 1; j < q; j++){
                if(cum[soldier[j].second] - cum[soldier[j].first - 1] < dec) dec = cum[soldier[j].second] - cum[soldier[j].first - 1];
            }
            res = max(tmp_res - dec, res);
            for(int j = left; j <= right; j++) section[j]++;
        }
        cout << res << "\n";
    }
    return 0;
}