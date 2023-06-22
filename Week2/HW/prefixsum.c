#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

long long int nums[2000001];

int main(){
	int n, q;
	while((scanf("%d %d", &n, &q)) != EOF){
		int i, index_a, index_b;
		long long int res = 0;
		nums[0] = 0;
		for(i = 1; i <= n; i++){
			scanf("%ld", &nums[i]);
			nums[i] += nums[i - 1];
		}
		
		int a, b;
		for(i = 0; i < q; i++){
			scanf("%d %d", &a, &b);
			if(a == b){
				if(nums[a] - nums[a - 1] > res){
					res = nums[a] - nums[a - 1];
					index_a = a;
					index_b = b;
				}
			}
			else if(a < b){
				if(nums[b] - nums[a - 1] > res){
					res = nums[b] - nums[a - 1];
					index_a = a;
					index_b = b;
				}
			}
			else{
				if(nums[b] + nums[n] - nums[a - 1] > res){
					res = nums[b] + nums[n] - nums[a - 1];
					index_a = a;
					index_b = b;
				}
			}
		}
		printf("Max_range: (%d,%d); Value: %ld\n", index_a, index_b, res);
	}
	return 0;
}
