#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
typedef struct _Node{
	int index;
	int val;
	struct _Node* left;
	struct _Node* right;
} Node;

Node* root = NULL;
long long int fp(int x);

void insert(Node** root, long long int val, int index);
void freetree(Node* root);

int main(void)
{
	int n, q;
	char s[100];
	while(scanf("%d %d", &n, &q) != EOF){
		int i, col;
		for(i = 1; i <= n; i++){
			scanf("%d", &col);
			scanf("%s", s);
			scanf("%s", s);
			if(col % 2 == 0){
				insert(&root, fp(col / 2), i);
			}
			else{
				insert(&root, 0, i);
			}
		}
		int x;
		while(q--){
			Node* cur = root;
			scanf("%d", &x);
			while(cur){
				if(cur->val > x){
					cur = cur->left;
				}
				else if(cur->val < x){
					cur = cur->right;
				}
				else{
					printf("%d\n", cur->index);
					break;
				}
			}
			if(cur == NULL){
				printf("Go Down Chicken 404\n");
			}
		}
		freetree(root);
		root = NULL;
	}	
	return 0;
}

long long int fp(int x){
	long long int res = 1;
	long long int pow = 2;
	while(x){
		if(x % 2 == 1){
			res = (res * pow) % MOD;
		}
		pow = (pow * pow) % MOD;
		x = x / 2;
	}
	return res;
}

void insert(Node** root, long long int val, int index){
	if((*root) == NULL){
		(*root) = (Node*)malloc(sizeof(Node));
		(*root)->val = val;
		(*root)->index = index;
		(*root)->left = NULL;
		(*root)->right = NULL;
	}
	else{
		Node* cur;
		Node* prev;
		int rep= 0;
		cur = *root;
		while(cur){
			if(cur->val > val){
				prev = cur;
				cur = cur->left;
			}
			else if(cur->val < val){
				prev = cur;
				cur = cur->right;
			}
			else{
				rep = 1;
				break;
			}
		}
		if(!rep){
			Node* leaf = (Node*)malloc(sizeof(Node));
			leaf->val = val;
			leaf->index = index;
			leaf->left = NULL;
			leaf->right = NULL;
			if(leaf->val < prev->val){
				prev->left = leaf;
			}
			else{
				prev->right = leaf;
			}
		}
	}
}

void freetree(Node* root){
	if(root == NULL){
		return;
	}
	freetree(root->left);
	freetree(root->right);
	free(root);
}
