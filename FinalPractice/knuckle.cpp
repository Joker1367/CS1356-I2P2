#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(vector<vector<int>>& knuckles, pair<bool, vector<int>>* charset, int now){
    charset[now].first = true;
    for(auto s: charset[now].second){
        for(auto itr: knuckles[s]){
            if(charset[itr].first) continue;
            dfs(knuckles, charset, itr);
        }
    }
    return;
}

int main(void){
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        pair<bool, vector<int>> charset[26];
        vector<vector<int>> knuckles(n);

        for(int i = 0; i < n; i++){
            string str; cin >> str;
            bool repeat[26] = {false};
            for(auto c: str){
                int idx = c - 'a';
                if(repeat[idx]) continue;
                repeat[idx] = true;
                knuckles[i].push_back(idx);
                charset[c - 'a'].second.push_back(i);
            }
        }

        int res = 0;
        for(int i = 0; i < 26; i++){
            if(charset[i].first || charset[i].second.empty()) continue;
            dfs(knuckles, charset, i);
            res++;
        }
        cout << res << "\n";
    }
    return 0;
}