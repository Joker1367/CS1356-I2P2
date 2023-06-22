#include <stdio.h>
#include <stdlib.h>

/* intuition
	(f_n, f_n - 1) = {{1, 1}, {1, 0}} * (f_n - 1, f_n)
				   = ({{1, 1}, {1, 0}} ^ (n - 1)) * (f_1, f_0)
	Use Fast Power to calculate the power of matrix -> O(log N)
*/ 

void fibo(long long int n);

int main(void){
	long long int index;
	
	while(scanf("%lld", &index) != EOF){
		fibo(index - 1);
	}
	return 0; 
}

void fibo(long long int n){
	if(n <= 1){
		printf("1\n");
		return;
	}
	long long int fib[2][2] = {{1, 1}, {1, 0}};
	long long int res[2][2] = {{1, 0}, {0, 1}};
	while(n != 0){
		long long int a = fib[0][0];
		long long int b = fib[0][1];
		long long int c = fib[1][0];
		long long int d = fib[1][1];
		if(n % 2 == 1){
			long long int e = res[0][0];
			long long int f = res[0][1];
			long long int g = res[1][0];
			long long int h = res[1][1];
			res[0][0] = ((e * a) % 1000000007 + (f * c) % 1000000007) % 1000000007;
			res[0][1] = ((e * b) % 1000000007 + (f * d) % 1000000007) % 1000000007;
			res[1][0] = ((g * a) % 1000000007 + (h * c) % 1000000007) % 1000000007;
			res[1][1] = ((g * b) % 1000000007 + (h * d) % 1000000007) % 1000000007; 
		}
		n = n / 2;
		fib[0][0] = ((a * a) % 1000000007 + (b * c) % 1000000007) % 1000000007;
		fib[0][1] = ((a * b) % 1000000007 + (b * d) % 1000000007) % 1000000007;
		fib[1][0] = ((c * a) % 1000000007 + (d * c) % 1000000007) % 1000000007;
		fib[1][1] = ((c * b) % 1000000007 + (d * d) % 1000000007) % 1000000007;
	}
	printf("%lld\n", res[0][0]);
}
