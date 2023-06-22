#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct ANS{
    long long int res = 0;
    int mini;
    int max_num;
    int max_num_index;
} answer;

int main(void){
    int n, a, b;
    long long int x, m;
    answer result;
    cin >> n >> x >> a >> b >> m;

    vector<pair<int, int>> table;
    long long cum[n + 1] = {0};
    for(int i = 1; i <= n; i++){
        int num; cin >> num;
        table.push_back({num, i});
    }
    sort(table.begin(), table.end());
    for(int i = 0; i < n; i++) cum[i + 1] += cum[i] + table[i].first;
    /*for(int i = 0; i < n; i++){
        cout << "(" << table[i].first << "," << table[i].second << ")" << " ";
    }
    cout << "\n";
    for(int i = 0; i <= n; i++) cout << cum[i] << " ";
    cout << "\n";*/
    for(int i = n; i >= 0; i--){
        long long int tmp_m = m;
        long long int tmp_res = 0;
        tmp_m -= x * i - (cum[n] - cum[n - i]);
        if(tmp_m < 0) continue;
        else{
            int right = n - i; int left = 0;
            while(left < right){
                int mid = (left + right) / 2;
                long long int cost = table[mid].first * (mid + 1) - cum[mid + 1];
                if(tmp_m < cost) right = mid;
                else left = mid + 1;
            }
            tmp_m -= table[left - 1].first * left - cum[left];
            long long int extra = tmp_m / left;

            tmp_res = a * i + b * (table[left - 1].first + extra);
            //cout << left << " " << i << "\n";
            if(tmp_res >= result.res){
                result.res = tmp_res;
                result.mini = table[left - 1].first + extra;
                result.max_num = table[n - i].first;
                result.max_num_index = table[n - i].second;
            }
        }
    }
    sort(table.begin(), table.end(), [](pair<int, int> a, pair<int, int> b){ return a.second < b.second; });
    cout << result.res << "\n";
    for(int i = 0; i < n; i++){
        if(table[i].first < result.mini) cout << result.mini;
        else if(table[i].first > result.max_num || (table[i].first == result.max_num && table[i].second >= result.max_num_index)) cout << x;
        else cout << table[i].first;
        if(i == n) cout << "\n";
        else cout << " ";
    }
    cout << "\n";
    return 0;
}