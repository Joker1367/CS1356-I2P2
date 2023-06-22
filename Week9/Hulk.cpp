#include <stdio.h>
#include <stdlib.h>

int comp(const void* a, const void* b){
	const int* da = (const int*) a;
	const int* db = (const int*) b;
	if(*da > *db){
		return 1;
	}
	else{
		return -1;
	} 
}

int main(void){
	int n, i, q;
	scanf("%d", &n);
	
	int* table = (int*)malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		scanf("%d", &table[i]);
	}
	qsort(table, n, sizeof(int), comp);
	
	scanf("%d", &q);
	while(q--){
		int num;
		scanf("%d", &num);
		if(num < table[0] || num > table[n - 1]){
			printf("0\n");
		}
		else{
			int ll = 0; int lr = n - 1; int rl = 0; int rr = n - 1;
			while(ll < lr){
				int mid = ll + (lr - ll) / 2;
				if(table[mid] >= num){
					lr = mid;
				}
				else{
					ll = mid + 1;
				}
			}
			while(rl < rr){
				int mid = rl + (rr - rl) / 2;
				if(table[mid] <= num){
					rl = mid + 1;
				}
				else{
					rr = mid;
				}
			}
			if(table[rl] == num){
				printf("%d\n", rl - lr + 1);
			}
			else{
				printf("%d\n", rl - lr);
			}
		}
	}
	return 0;
}