#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include "function.h"
#define MAX_N 10004

typedef struct _NODE {
	int level;
	struct _NODE *left_child, *right_child;
} Node;

#define left left_child
#define right right_child

void build_tree(Node **now, int *arr, int l, int r);
int query_heatstroke(Node *now, int x);
void eat_rat(Node **root, int x);
void buy_rat(Node **root, int x);

int n, q;
int a[MAX_N];

void build_tree(Node **now, int *arr, int l, int r){
	if(r < l){
		return;
	}
	else{
		(*now) = (Node*)malloc(sizeof(Node));
		int mid = l + (r - l) / 2;
		
		(*now)->level = arr[mid];
		(*now)->left_child = NULL;
		(*now)->right_child = NULL;
		build_tree(&((*now)->left_child), arr, l, mid - 1);
		build_tree(&((*now)->right_child), arr, mid + 1, r);
	}
}

int query_heatstroke(Node *now, int x)
{
    Node *cur = now;

    while (cur != NULL)
    {
        if (cur->level == x)
        {
            return 1;
        }
        else if (cur->level > x)
        {
            cur = cur->left;
        }
        else
        {
            cur = cur->right;
        }
    }
    return 0;
}

void eat_rat(Node **root, int x)
{
	/*Node* dummy = (Node*)malloc(sizeof(Node));
	dummy->level = -1;
	dummy->left = *root;
	dummy->right = *root*;*/
	
    Node *cur = *root;
    Node *prev;

    int find = 1;
    while (find)
    {
        if (cur->level > x)
        {
            prev = cur;
            cur = cur->left;
        }
        else if (cur->level < x)
        {
            prev = cur;
            cur = cur->right;
        }
        else
        {
            if (cur->right == NULL && cur->left == NULL)
            {
            	if(cur == *root){
            		free(cur);
            		*root = NULL;
            		find = 0;
				}
                else if (prev->right == cur)
                {
                    prev->right = NULL;
                    free(cur);
                    cur = NULL;
                    find = 0;
                }
                else
                {
                    prev->left = NULL;
                    free(cur);
                    cur = NULL;
                    find = 0;
                }
            }
            else if (cur->right == NULL)
            {
            	if(cur == *root){
            		*root = cur->left;
            		free(cur);
            		cur = NULL;
            		find = 0;
				}
                else if (prev->right == cur)
                {
                    prev->right = cur->left;
                    free(cur);
                    cur = NULL;
                    find = 0;
                }
                else
                {
                    prev->left = cur->left;
                    free(cur);
                    cur = NULL;
                    find = 0;
                }
            }
            else if (cur->left == NULL)
            {
            	if(cur == *root){
            		*root = cur->right;
            		free(cur);
            		cur = NULL;
            		find = 0;
				}
                else if (prev->right == cur)
                {
                    prev->right = cur->right;
                    free(cur);
                    cur = NULL;
                    find = 0;
                }
                else
                {
                    prev->left = cur->right;
                    free(cur);
                    cur = NULL;
                    find = 0;
                }
            }
            else
            {
                Node *tmp = cur;
                prev = cur;
                cur = cur->right;
                if (cur->left != NULL)
                {
                    while (cur->left != NULL)
                    {
                        prev = cur;
                        cur = cur->left;
                    }
                    if (cur->right == NULL)
                    {
                        tmp->level = cur->level;
                        prev->left_child = NULL;
                        free(cur);
                        cur = NULL;
                        find = 0;
                    }
                    else
                    {
                        tmp->level = cur->level;
                        prev->left = cur->right;
                        free(cur);
                        cur = NULL;
                        find = 0;
                    }
                }
                else
                {
                    tmp->level = cur->level;
                    tmp->right = cur->right;
                    free(cur);
                    cur = NULL;
                    find = 0;
                }
            }
        }
    } 
    //free(dummy);
}

void buy_rat(Node **root, int x){
	if((*root) == NULL){
		(*root) = (Node*)malloc(sizeof(Node));
		(*root)->level = x;
		(*root)->left_child = NULL;
		(*root)->right_child = NULL;
	}
	else{
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->level = x;
		new_node->left_child = NULL;
		new_node->right_child = NULL;
		
		Node* cur = (*root);
		while(cur){
			if(cur->level > x){
				if(cur->left_child == NULL){
					cur->left_child = new_node;
					break;
				}
				else{
					cur = cur->left_child;	
				}
			}
			else{
				if(cur->right == NULL){
					cur->right_child = new_node;
					break;
				}
				else{
					cur = cur->right_child;
				}
			}
		}		
	}
}

int main() {
	scanf("%d",&n);
	int i;
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	Node *root = NULL;
	build_tree(&root,a,0,n-1);
	scanf("%d",&q);
	char op[20];
	while(q--) {
		int x;
		scanf("%s",op);
		scanf("%d",&x);
		if(strcmp(op,"heatstroke")==0) {
			if(query_heatstroke(root,x)!=0) {
				puts("We might as well eat it.");
				eat_rat(&root,x);
			}
			else puts("No dinner tonight.");
		}
		else if(strcmp(op,"buy")==0) {
			buy_rat(&root,x);
		}
	}
	return 0;
}
