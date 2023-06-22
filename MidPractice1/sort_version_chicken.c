#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef struct _Pair{
	int index;
	int val;
} Pair;

long long int fp(int x);
int comp_Pair(const void* a, const void* b);

int main(void)
{
	int n, q;
	char s[100];
	while(scanf("%d %d", &n, &q) != EOF){
		int i, col;
		Pair* table = (Pair*)malloc(n * sizeof(Pair));
		for(i = 0; i < n; i++){
			scanf("%d", &col);
			scanf("%s", s);
			scanf("%s", s);
			if(col % 2 == 0){
				table[i].index = i + 1;
				table[i].val = fp(col / 2);
			}
			else{
				table[i].index = i + 1;
				table[i].val = 0;
			}
		}
		/*for(i = 0; i < n; i++){
			printf("%d %d\n", table[i].val, table[i].index);
		}*/
		qsort(table, n, sizeof(Pair), comp_Pair);
		/*for(i = 0; i < n; i++){
			printf("%d %d\n", table[i].val, table[i].index);
		}*/
		int x;
		while(q--){
			int l = 0; int r = n - 1; int i; int find = 0;
			scanf("%d", &x);
			while(l <= r){
				int mid = l + (r - l) / 2;
				if(table[mid].val > x){
					r = mid - 1;
				}
				else if(table[mid].val < x){
					l = mid + 1;
				}
				else{
					find = 1;
					r = mid;
					while(l <= r){
						int m = l + (r - l) / 2;
						if(table[m].val == x){
							r = m - 1;
						}
						else{
							l = m + 1;
						}
					}
					printf("%d\n", table[l].index);
					break;
				}
			}
			if(!find){
				printf("Go Down Chicken 404\n");
			}
			
		}
		free(table);
	}	
	return 0;
}

long long int fp(int x){
	long long int res = 1;
	long long int pow = 2;
	while(x){
		if(x % 2 == 1){
			res = (res * pow) % MOD;
		}
		pow = (pow * pow) % MOD;
		x = x / 2;
	}
	return res;
}

int comp_Pair(const void* a, const void* b){
	const Pair* p = (const Pair*) a;
	const Pair* q = (const Pair*) b;
	if(p->val < q->val){
		return -1;
	}
	else if(p->val > q->val){
		return 1;
	}
	else{
		if(p->index < q->index){
			return -1;
		}
		else{
			return 1;
		}
	}
}
