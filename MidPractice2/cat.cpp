#include <iostream>
#include <vector>

using namespace std;

int x_axis[500];
int y_axis[500];
int visited[500] = {0};
int group[501] = {0};

int n, k, r;
int group_type = 0;

bool dist(int i, int j){
    if((x_axis[i] - x_axis[j]) * (x_axis[i] - x_axis[j]) + (y_axis[i] - y_axis[j]) * (y_axis[i] - y_axis[j]) <= (r * r))
        return true;
    else 
        return false;
}

void dfs(int parent, int now){
    visited[now] = 1;
    group[group_type]++;
    for(int i = 0; i < n; i++){
        if(i == parent) continue;
        if(visited[i] == 1) continue;
        if(dist(now, i)){
            dfs(now, i);
        }
    }
}

int main(void){
    int t;
    cin >> t;
    while(t--){
        cin >> n >> r >> k;
        int less = 0; int more = 0;
        for(int i = 0; i < n; i++){
            cin >> x_axis[i] >> y_axis[i];
        }
        for(int i = 0; i < n; i++){
            if(visited[i] == 0){
                group_type++;
                dfs(-1, i);
            }
        }
        for(int i = 1; i <= group_type; i++){
            if(group[i] >= k) more++;
            else less++;
            group[i] = 0;
        }
        cout << less << " " << more << "\n";
        for(int i = 0; i < n; i++){
            visited[i] = 0;
        }
        group_type = 0;
    }
    return 0;
}