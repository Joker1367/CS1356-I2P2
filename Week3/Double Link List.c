#include<string.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct _NODE
{
	char character;
	struct _NODE *ptr_to_next_node;
	struct _NODE *ptr_to_prev_node;
} Node;

void insert(Node**, char);

void deletion(Node**);

void backspace(Node**);

void go_left(Node**, int);

void go_right(Node**, int);

void go_home(Node**);

void go_end(Node**);

void show();

Node* head;
Node* tail;
int len = 1;

void insert(Node** node, char c){
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->character =  c;
	
	if((*node) == tail){
		new_node->ptr_to_next_node = head;
		head->ptr_to_prev_node = new_node;
		new_node->ptr_to_prev_node = *node;
		(*node)->ptr_to_next_node = new_node;
		tail = new_node;
	}
	else{
		new_node->ptr_to_next_node = (*node)->ptr_to_next_node;
		new_node->ptr_to_prev_node = *node;
		(*node)->ptr_to_next_node->ptr_to_prev_node = new_node;
		(*node)->ptr_to_next_node = new_node;
	}
	len++;
}

void deletion(Node** node){
	if((*node) == tail){
		return;
	}
	if((*node)->next == tail){
		tail = *node;
	}
	Node* del_node = (*node)->ptr_to_next_node;
	(*node)->ptr_to_next_node = (*node)->ptr_to_next_node->ptr_to_next_node;
	(*node)->ptr_to_next_node->ptr_to_prev_node = *node;
	free(del_node);
	len--;
}

void backspace(Node** node){
	if((*node) == head){
		return;
	}
	if((*node) == tail){
		tail = (*node)->prev;
	}
	Node* tmp = (*node)->ptr_to_prev_node;
	(*node)->ptr_to_prev_node->ptr_to_next_node = (*node)->ptr_to_next_node;
	(*node)->ptr_to_next_node->ptr_to_prev_node = (*node)->ptr_to_prev_node;
	free(*node);
	(*node) = tmp;
	len--;
}

void go_left(Node** node, int index){
	index = index % len;
	while(index--){
		(*node) = (*node)->ptr_to_prev_node;
	}
}

void go_right(Node** node, int index){
	index = index % len;
	while(index--){
		(*node) = (*node)->ptr_to_next_node;
	}
}

void go_home(Node** node){
	(*node) = head;
}

void go_end(Node** node){
	(*node) = tail;
}

#define ll long long int
#define next ptr_to_next_node
#define prev ptr_to_prev_node
#define ch character



int n, num;
char buf[10], intype;
Node *cursor;
extern Node *head, *tail;

void show()
{
	if(head == NULL){
		printf("\n");
		return;
	}
	Node *now = head->next;
	while(now != head)
	{
		printf("%c ", now->ch);
		now = now->next;
	}
	printf("\n");
}

int main()
{
	scanf("%d",&n);
	head = (Node*)malloc(sizeof(Node));
	head->next = head->prev = head;
	cursor = tail = head;
	while(n--)
	{
		scanf("%s",buf);
		if(!strcmp(buf,"insert"))
		{
			getchar();
			scanf("%c",&intype);
			insert(&cursor, intype); 
		}
		else if(!strcmp(buf,"deletion"))
		{
			deletion(&cursor); 
		}
		else if(!strcmp(buf,"backspace"))
		{
			backspace(&cursor); 
		}
		else if(!strcmp(buf,"go_left"))
		{
            scanf("%d", &num);
			go_left(&cursor, num); 
		}
        else if(!strcmp(buf,"go_right"))
		{
            scanf("%d", &num);
			go_right(&cursor, num); 
		}
        else if(!strcmp(buf,"go_home"))
		{
			go_home(&cursor); 
		}
        else if(!strcmp(buf,"go_end"))
		{
			go_end(&cursor); 
		}
		else if(!strcmp(buf,"show"))
		{
			show();
		}
	}
	return 0;
}



