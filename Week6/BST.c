#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE
{
    int level;
    struct _NODE *left_child, *right_child;
} Node;

#define left left_child
#define right right_child

void build_tree(Node **now, int *arr, int l, int r);
int query_heatstroke(Node *now, int x);
void eat_rat(Node **root, int x);

void build_tree(Node **now, int *arr, int l, int r)
{
    if (r < l)
    {
        return;
    }

    (*now) = (Node *)malloc(sizeof(Node));
    int mid = l + (r - l) / 2;

    (*now)->level = arr[mid];
    (*now)->left = NULL;
    (*now)->right = NULL;
    build_tree(&((*now)->left), arr, l, mid - 1);
    build_tree(&((*now)->right), arr, mid + 1, r);
}

void preorder(Node *node)
{
    Node *cur = node;
    if (cur == NULL)
    {
        printf("NULL ");
        return;
    }
    else
    {
        printf("%d ", cur->level);
	}
    preorder(cur->left);
    preorder(cur->right);
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

#define MAX_N 1000006

int n, q;
int a[MAX_N];

int main()
{
    scanf("%d", &n);
    int i;
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    Node *root = NULL;
    build_tree(&root, a, 0, n - 1);
    preorder(root);
    scanf("%d", &q);
    while (q--)
    {
        int x;
        scanf("%d", &x);
        if (query_heatstroke(root, x) != 0)
        {
            puts("We might as well eat it.");
            eat_rat(&root, x);
        }
        else{
        	puts("No dinner tonight.");
		}
        preorder(root);
    }
    return 0;
}
