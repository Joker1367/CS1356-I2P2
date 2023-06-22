#include <stdio.h>
#include <stdlib.h>

char s[500000];

int main(void){
	int alpha[26];
	int i;
	
	for(i = 0; i < 26; i++){
		alpha[i] = i;
	}
	
	int n, q;
	scanf("%d %d", &n, &q);
	scanf("%s", s);
	
	while(q){
		char c1, c2, c3, c4;
		scanf("%c%c%c%c", &c1, &c2, &c3, &c4);
		printf("%c %c", c2, c4);
		int tmp = alpha[c2 - 'a'];
		alpha[c2 - 'a'] = alpha[c4 - 'a'];
		alpha[c4 - 'a'] = tmp;
		q--;
	}
	
	for(i = 0; i < n; i++){
		char c = 'a' + alpha[s[i] - 'a'];
		printf("%c", c);
	}
	printf("\n");
}
