#include<stdio.h>

void print_binary(int n, int i){
	int k;
	for(k = i - 1; k >= 0; k--){
		if((n >> k) & 1){
			printf("1");
		}
		else{
			printf("0");
		}
	}
}

typedef union {
	float f;
	struct{
		unsigned int Mantissa : 23;
		unsigned int Exponent : 8;
		unsigned int Sign : 1;
	} IEEE_754;
} myfloat;

int main(void){
	myfloat f;
	while(scanf("%f", &f.f) != EOF){
		print_binary(f.IEEE_754.Sign, 1);
		print_binary(f.IEEE_754.Exponent, 8);
		print_binary(f.IEEE_754.Mantissa, 23);
		printf("\n");
	}
	
	return 0;
}
