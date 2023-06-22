#include <iostream>
#include <stdlib.h>
#include <queue>

typedef struct _node{
	char type;
	bool visited;
} Node;

using namespace std;

int main(void)
{
	int m, n;
	int res = 0; int dist = 0;
	queue<pair<int, int>> que;
	cin >> m >> n;
	Node map[m][n];
	
	int init_i, init_j;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			cin >> map[i][j].type;
			map[i][j].visited = false;
			if(map[i][j].type == 'I'){
				que.push({i, j});
				map[i][j].visited = true;
			}
		}
	}
	while(!que.empty()){
		int size = que.size();
		for(int i = 0; i < size; i++){
			auto sit = que.front();
			int x = sit.first; int y = sit.second;
			if(map[x][y].type == 'T'){
				res = dist;
			}
			if(x > 0 && map[x - 1][y].visited == false && map[x - 1][y].type != 'C'){
				map[x - 1][y].visited = true;
				que.push({x - 1, y});
			}
			if(x < m - 1 && map[x + 1][y].visited == false && map[x + 1][y].type != 'C'){
				map[x + 1][y].visited = true;
				que.push({x + 1, y});
			}
			if(y > 0 && map[x][y - 1].visited == false && map[x][y - 1].type != 'C'){
				map[x][y - 1].visited = true;
				que.push({x, y - 1});
			}
			if(y < n - 1 && map[x][y + 1].visited == false && map[x][y + 1].type != 'C'){
				map[x][y + 1].visited = true;
				que.push({x, y + 1});
			}
			que.pop();
		}
		dist++;
	}

    bool find = false;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(map[i][j].visited == false && map[i][j].type == 'T'){
                find = true;
                break;
            }
        }
    }
	
    if(find)
        cout << -1 << "\n";
    else
	    cout << res << "\n";
	return 0;
}