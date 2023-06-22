#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long int cum[300001] = {0};

int main(void){
    int t; cin >> t;
    while(t--){
        int n, p, k; cin >> n >> p >> k;
        vector<int> cost;
        for(int i = 0; i < n; i++){
            int num; cin >> num;
            cost.push_back(num);
        }
        sort(cost.begin(), cost.end());
        for(int i = 1; i <= n; i++){
            if(i < k) cum[i] = cum[i - 1] + cost[i - 1];
            else cum[i] = cum[i - k] + cost[i - 1];
        }
        int res = 0;
        for(int i = 1; i <= n; i++){
            if(cum[i] <= p) res = i;
        }
        cout << res << "\n";
    }
    return 0;
}