#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
	int val;
	struct _Node* left;
	struct _Node* right;
} Node;

Node* buildTree(int* inorder, int* postorder, int inorder_start, int inorder_end){
	if(inorder_start > inorder_end){
		return NULL;
	}
	int i;
	Node* root;
	for(i = inorder_start; i <= inorder_end; i++){
		if(inorder[i] == *postorder){
			root = (Node*)malloc(sizeof(Node));
			root->val = inorder[i];
			root->right = buildTree(inorder, postorder + 1, i + 1, inorder_end);
			root->left = buildTree(inorder, postorder + inorder_end - i + 1, inorder_start, i - 1);
			break;
		}
	}
	return root;
}

void preorder(Node* root){
	if(root == NULL){
		return;
	}
	printf("%d ", root->val);
	preorder(root->left);
	preorder(root->right);
}

void freeTree(Node* root){
	if(root == NULL){
		return;
	}
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

int main(void)
{
	int n, i;
	int id = 1;
	while(scanf("%d", &n) != EOF){
		int inorder[100];
		int postorder[100];
		for(i = 0; i < n; i++){
			scanf("%d", &inorder[i]);
		}
		for(i = 0; i < n; i++){
			scanf("%d", &postorder[n - 1 - i]);
		}
		
		Node* root = buildTree(inorder, postorder, 0, n - 1);
		printf("testcase%d: ", id++);
		preorder(root);
		printf("\n");
		freeTree(root);
	}
	
	return 0;
}
