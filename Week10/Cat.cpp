#include <iostream>

using namespace std;

int x_axis[10000];
int y_axis[10000];
int visited[10000] = {0};
int group[10001] = {0};
int group_type = 1;
int n, r;

bool dist(int next, int now){
	if((x_axis[now] - x_axis[next]) * (x_axis[now] - x_axis[next]) + (y_axis[now] - y_axis[next]) * (y_axis[now] - y_axis[next]) <= (r * r)) 
		return true;
	else
		return false;
}

void dfs(int parent, int now){
	visited[now] = group_type;
	for(int i = 0; i < n; i++){
		if(i == parent) continue;
		if(visited[i] == group_type) continue;
		if(dist(i, now)){
			dfs(now, i);
		}
	}
}

int main(void){
	cin >> n >> r;
	for(int i = 0; i < n; i++){
		cin >> x_axis[i] >> y_axis[i];
	}

	int blackhole = 0; int cat_num = 0;
	for(int i = 0; i < n; i++){
		if(visited[i] == false){
			dfs(-1, i);
			group_type++;
		}
	}

	for(int i = 0; i < n; i++){
		group[visited[i]]++;
	}
	for(int i: group){
		if(i == 0) continue;
		else if(i == 1) cat_num++;
		else blackhole++;
	}
	cout << cat_num << " " << blackhole << "\n";
	return 0;
}