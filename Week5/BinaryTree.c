#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE
{
    int number;
    struct _NODE *ptr_to_right_node;
    struct _NODE *ptr_to_left_node;
} Node;

#define right ptr_to_right_node
#define left ptr_to_left_node
#define num number

Node *buildTree(int *inorder, int *preorder, int inorder_start, int inorder_end)
{
    if (inorder_start > inorder_end)
    {
        return NULL;
    }

    int i;
    Node *node = (Node *)malloc(sizeof(Node));
    for (i = inorder_start; i <= inorder_end; i++)
    {
        if (inorder[i] == *preorder)
        {
            node->number = inorder[i];
            node->left = buildTree(inorder, preorder + 1, inorder_start, i - 1);
            node->right = buildTree(inorder, preorder + i - inorder_start + 1, i + 1, inorder_end);
            break;
        }
    }
    return node;
}

void showPostorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    showPostorder(root->left);
    showPostorder(root->right);
    printf("%d ", root->number);
}

void freeTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int n;

int main(void)
{
    int id = 1;
    while (~scanf("%d", &n))
    {
        int inorder[100], preorder[100];

        for (int i = 0; i < n; i++)
            scanf("%d", &inorder[i]);

        for (int i = 0; i < n; i++)
            scanf("%d", &preorder[i]);

        Node *root = buildTree(inorder, preorder, 0, n - 1);

        printf("testcase%d: ", id++);
        showPostorder(root);
        printf("\n");
        freeTree(root);
    }
    return 0;
}