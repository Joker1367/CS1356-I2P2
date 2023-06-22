#include <stdio.h>
#include <stdlib.h>

int main(void){
	int row, col, i, num;
	int res;
	scanf("%d %d", &row, &col);
	scanf("%d", &res);
	for(i = 1; i < row * col; i++){
		scanf("%d", &num);
		res = (res < num) ? res : num;
	}
	printf("%d\n", res);
}
