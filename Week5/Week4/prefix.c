#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	char s[2000];
	char p[2000];
	int amt;
	
	while(scanf("%s", s) != EOF){
		scanf("%s", p);
		int pre[2000] = {0};
		
		int i, j;
		int amt = 0;
		for(i = 0; i < strlen(s); i++){
			for(j = 0; j < strlen(p) && i + j < strlen(s); j++){
				if(s[i + j] != p[j]){
					break;
				}
			}
			if(j == strlen(p)){
				pre[i + strlen(p)] = amt + 1;
				amt++;
			}
		}
		
		int change = 0;
		for(i = 1; i <= strlen(s); i++){
			if(pre[i] != 0){
				change = pre[i];
			}
			else{
				pre[i] = change;
			}
		}
		
		/*for(i = 1; i <= strlen(s); i++){
			printf("%d ", pre[i]);
		}
		printf("\n");*/
		
		scanf("%d", &amt);
		int res = 0;
		while(amt--){
			int a, b;
			int sum;
			scanf("%d %d", &a, &b);
			if(b - a + 1 >= strlen(p)){
				if(strlen(p) == 1){
					sum = pre[b] - pre[a - 1];
				}
				else{
					sum = pre[b] - pre[a + strlen(p) - 2];
				}
				res = (res > sum) ? res : sum;
			}
			else{
				continue;
			}
		}
		printf("%d\n", res); 
	}
	return 0;
}
