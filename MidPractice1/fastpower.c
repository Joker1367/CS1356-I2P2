#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main(void){
	int t;
	long long int x;
	scanf("%d", &t);
	while(t--){
		scanf("%lld", &x);
		switch(x){
			case 1:
				printf("1\n");
				break;
			case 2:
				printf("12\n");
				break;
			case 3:
				printf("13\n");
				break;
			default:
				printf("%d\n", fp(x - 3));
				break;
		}
	}
	return 0;
}

int fp(long long int x){
	long long int mat[3][3] = {{1, 2, 1}, {1, 0, 0}, {0, 1, 0}};
	long long int p1, p2, p3, tp1, tp2, tp3;
	long long int p00, p01, p02, p10, p11, p12, p20, p21, p22;
	p1 = 13; p2 = 12; p3 = 1;
	while(x){
		if(x % 2 == 1){
			tp1 = (((p1 * mat[0][0]) % MOD) + ((p2 * mat[0][1]) % MOD) + ((p3 * mat[0][2]) % MOD)) % MOD;
			tp2 = (((p1 * mat[1][0]) % MOD) + ((p2 * mat[1][1]) % MOD) + ((p3 * mat[1][2]) % MOD)) % MOD;
			tp3 = (((p1 * mat[2][0]) % MOD) + ((p2 * mat[2][1]) % MOD) + ((p3 * mat[2][2]) % MOD)) % MOD;
			p1 = tp1;
			p2 = tp2;
			p3 = tp3;
		}
		p00 = (((mat[0][0] * mat[0][0]) % MOD) + ((mat[0][1] * mat[1][0]) % MOD) + ((mat[0][2] * mat[2][0]) % MOD)) % MOD;
		p01 = (((mat[0][0] * mat[0][1]) % MOD) + ((mat[0][1] * mat[1][1]) % MOD) + ((mat[0][2] * mat[2][1]) % MOD)) % MOD;
		p02 = (((mat[0][0] * mat[0][2]) % MOD) + ((mat[0][1] * mat[1][2]) % MOD) + ((mat[0][2] * mat[2][2]) % MOD)) % MOD;
		p10 = (((mat[1][0] * mat[0][0]) % MOD) + ((mat[1][1] * mat[1][0]) % MOD) + ((mat[1][2] * mat[2][0]) % MOD)) % MOD;
		p11 = (((mat[1][0] * mat[0][1]) % MOD) + ((mat[1][1] * mat[1][1]) % MOD) + ((mat[1][2] * mat[2][1]) % MOD)) % MOD;
		p12 = (((mat[1][0] * mat[0][2]) % MOD) + ((mat[1][1] * mat[1][2]) % MOD) + ((mat[1][2] * mat[2][2]) % MOD)) % MOD;
		p20 = (((mat[2][0] * mat[0][0]) % MOD) + ((mat[2][1] * mat[1][0]) % MOD) + ((mat[2][2] * mat[2][0]) % MOD)) % MOD;
		p21 = (((mat[2][0] * mat[0][1]) % MOD) + ((mat[2][1] * mat[1][1]) % MOD) + ((mat[2][2] * mat[2][1]) % MOD)) % MOD;
		p22 = (((mat[2][0] * mat[0][2]) % MOD) + ((mat[2][1] * mat[1][2]) % MOD) + ((mat[2][2] * mat[2][2]) % MOD)) % MOD;
		mat[0][0] = p00; mat[0][1] = p01; mat[0][2] = p02; mat[1][0] = p10; mat[1][1] = p11; mat[1][2] = p12; mat[2][0] = p20; mat[2][1] = p21; mat[2][2] = p22;
		x = x / 2;
	}
	return p1 % MOD;
}
