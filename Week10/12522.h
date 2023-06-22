#include <iostream>

using namespace std;

int n, r;
int group_type = 0;
int x_axis[1000] = {0};
int y_axis[1000] = {0};
int group[1000] = {0};
int visited[1000] = {0};

bool dist(int i, int j){
	if((x_axis[i] - x_axis[j]) * (x_axis[i] - x_axis[j]) + (y_axis[i] - y_axis[j]) * (y_axis[i] - y_axis[j]) <= r * r) return true;
	else return false;
}

void dfs(int parent, int now){
	visited[now] = group_type;
	for(int i = 0; i < n; i++){
		if(visited[i] == group_type || i == parent) continue;
		else if(dist(now, i)){
			dfs(now, i);
		}
	}
}

int main(void){
	cin >> n >> r;
	int cat = 0; int black = 0;
	for(int i = 0; i < n; i++) cin >> x_axis[i] >> y_axis[i];
	for(int i = 0; i < n; i++){
		if(visited[i] == 0){
			group_type++;
			dfs(-1, i);
		}
	}
	for(int i = 0; i < n; i++) group[visited[i]]++;
	for(int i = 1; i <= group_type; i++){
		if(group[i] == 1) cat++;
		else black++;
	}
	cout << cat << " " << black << "\n";
}