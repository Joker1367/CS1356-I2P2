#include <stdio.h>
#include <stdlib.h>

long long int pre[2000000] = {0};

int main(void){
	int n, q, i;
	scanf("%d %d", &n, &q);
	
	int val, neg;
	int find = 0;
	for(i = 1; i <= n; i++){
		scanf("%d", &val);
		if(val < 0 && !find){
			neg = i;
			find = 1;
		}
		pre[i] = pre[i - 1] + val;
	}
	
	if(!find){
		neg = n + 1;
	}
	
	while(q--){
		int l, r, m;
		scanf("%d %d %d", &l, &r, &m);
		if(r - l + 1 < m){
			if(neg >= l && neg <= r){
				printf("%lld\n", pre[neg - 1] - pre[l - 1]);
			}
			else if(neg < l){
				printf("0\n");
			}
			else{
				printf("%lld\n", pre[r] - pre[l - 1]);
			}
		}
		else{
			if(neg >= l && neg <= l + m - 1){
				printf("%lld\n", pre[neg - 1] - pre[l - 1]);
			}
			else if(neg < l){
				printf("0\n");
			}
			else{
				printf("%lld\n", pre[l + m - 1] - pre[l - 1]);
			}
		}
	}
	return 0;
}
