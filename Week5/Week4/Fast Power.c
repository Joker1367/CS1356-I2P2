#include<stdio.h>
#include<stdlib.h>

//775477547754 775477547754 10235876
long long int fpw(long long int x, long long int y, long long int m);

int main(void){
	long long int x, y, m;
	long long int res; 
	scanf("%lld %lld %lld", &x, &y, &m);
	x = x % m;
	
	res = fpw(x, y, m);
	
	printf("%lld\n", res);
	return 0; 
}

long long int fpw(long long int x, long long int y, long long int m){
	long long int res = 1;
	while(y != 0){
		if(y % 2 == 1){
			res = (res * x) % m;
		}
		y = y / 2;
		x = (x * x) % m;
	}
	return res % m;
}


