#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _Node{
    char s[5];
    struct _Node* left;
    struct _Node* right;
} Node;

int index;

Node* build(char* s){
	while(s[index] == ' ' && index < strlen(s)){
		index++;
	}
	Node* root = (Node*)malloc(sizeof(Node));
	if(index < strlen(s)){
		if(s[index] == '+'){
			strcpy(root->s, "+");
			index++;
			root->left = build(s);
			root->right = build(s);
		}
		else if(s[index] == '-'){
			strcpy(root->s, "-");
			index++;
			root->left = build(s);
			root->right = build(s);
		}
		else if(s[index] == '*'){
			strcpy(root->s, "*");
			index++;
			root->left = build(s);
			root->right = build(s);
		}
		else if(s[index] == '/'){
			strcpy(root->s, "/");
			index++;
			root->left = build(s);
			root->right = build(s);
		}
		else{
			int i;
			for(i = 0; s[index] != ' ' && index < strlen(s); i++, index++){
				(root->s)[i] = s[index];
			}
			for(; i < 5; i++){
				(root->s)[i] = '\0';
			}
			root->left = NULL;
			root->right = NULL;
		}
		return root;
	}
	else{
		free(root);
	}
	return NULL;
}

void inorder(Node* root){
	if(root == NULL){
		return;
	}
	inorder(root->left);
	printf("%s", root->s);
	inorder(root->right);
}

void delete_tree(Node* root){
	if(root == NULL){
		return;
	}
	
	delete_tree(root->left);
	delete_tree(root->right);
	free(root);
}

int calculate(Node* root, int x, int y, int z){
	if(strcmp(root->s, "+") == 0){
		int res1 = calculate(root->left, x, y, z);
		int res2 = calculate(root->right, x, y, z);
		return res1 + res2;
	}
	else if(strcmp(root->s, "*") == 0){
		int res1 = calculate(root->left, x, y, z);
		int res2 = calculate(root->right, x, y, z);
		return res1 * res2;
	}
	else if(strcmp(root->s, "-") == 0){
		int res1 = calculate(root->left, x, y, z);
		int res2 = calculate(root->right, x, y, z);
		return res1 - res2;
	}
	else if(strcmp(root->s, "/") == 0){
		int res1 = calculate(root->left, x, y, z);
		int res2 = calculate(root->right, x, y, z);
		return res1 / res2;
	}
	else if(strcmp(root->s, "x") == 0){
		return x;
	}
	else if(strcmp(root->s, "y") == 0){
		return y;
	}
	else if(strcmp(root->s, "z") == 0){
		return z;
	}
	else{
		int i;
		int res = 0;
		for(i = 0; (root->s)[i] != '\0'; i++){
			char c = (root->s)[i];
			res = res * 10 + (c - '0');
		}
		return res;
	}
}

int main(void){
	char s[200];
	int x, y, z;
	gets(s);
	scanf("%d %d %d", &x, &y, &z);
	
	Node* root = (Node*)malloc(sizeof(Node));
	index = 0;
	root = build(s);
	
	inorder(root);
	printf("\n");
	printf("%d\n", calculate(root, x, y, z));
	delete_tree(root);
	return 0;
}
