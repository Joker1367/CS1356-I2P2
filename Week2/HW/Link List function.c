#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _NODE
{
    char color[10];
    struct _NODE *next;
} Node;

void insert(Node**, char*, int);

void erase1(Node**, int);

void erase2(Node**, char*);

void reverse(Node**, int, int);

void insert(Node** node, char* color, int index){
	Node* new_node = (Node*)malloc(sizeof(Node));
	strcpy(new_node->color, color);
	Node* prev = *node;
	Node* cur = (*node)->next;
	
	while(index-- && cur != NULL){
		cur = cur->next;
		prev = prev->next;
	}
	
	prev->next = new_node;
	new_node->next = cur;
}

void erase1(Node** node, int index){
	Node* prev = *node;
	Node* cur = (*node)->next;
	if(cur == NULL){
		return;
	}
	
	while(index > 1 && cur->next != NULL){
		cur = cur->next;
		prev = prev->next;
		index--;
	}
	
	prev->next = cur->next;
	free(cur);
}

void erase2(Node** node, char* color){
	Node* prev = *node;
	Node* cur = (*node)->next;
	
	if(cur == NULL){
		return;
	}
	
	while(cur != NULL){
		if(strcmp(cur->color, color) == 0){
			prev->next = cur->next;
			free(cur);
			cur = cur->next;
		}
		else{
			prev = prev->next;
			cur = cur->next;
		}
	}
}

void reverse(Node** node, int index_1, int index_2){
	if(index_2 <= index_1){
		return;
	}
	Node* prev = *node;
	Node* cur = (*node)->next;
	if(cur == NULL){
		return;
	}
	
	int i = index_1;
	while(i > 1 && cur != NULL){
		cur = cur->next;
		prev = prev->next;
		i--;
	}
	
	if(cur == NULL){
		return;
	}
	else{
		Node* cons = prev;
		cur = cur->next;
		prev = prev->next;
		int i;
		for(i = index_1 + 1; i <= index_2 && cur != NULL; i++){
			Node* tmp = cur->next;
			cur->next = prev;
			prev = cur;
			cur = tmp;
		}
		cons->next->next = cur;
		cons->next = prev;
	}
}

void show(Node **head) {
    Node *now = (*head)->next;
    while(now!=NULL) {
        printf("%s ", now->color);
        now = now->next;
    }
    puts("");
}

int n;
char buf[100];
int num1, num2;
Node *head;

int main(void) {
    head = (Node*)malloc(sizeof(Node)); // create an empty node
    memset(head->color,'\0',sizeof(head->color));
    head->next = NULL;
    scanf("%d",&n);
    while(n--) {
        scanf("%s",buf);
        if(!strcmp(buf,"insert")) {
            scanf("%s%d",buf,&num1);
            insert(&head, buf, num1); // insert <color> <dest>
        }
        else if(!strcmp(buf,"erase1")) {
            scanf("%d",&num1);
            erase1(&head, num1); // erase1 <dest>
        }
        else if(!strcmp(buf,"erase2")) {
            scanf("%s",buf);
            erase2(&head, buf); // erase2 <color>
        }
        else if(!strcmp(buf,"reverse")) {
            scanf("%d%d",&num1,&num2);
            reverse(&head, num1, num2); // reverse <dest1> <dest2>
        }
        else if(!strcmp(buf,"show")) {
            show(&head);
        }
    }
    return 0;
}


