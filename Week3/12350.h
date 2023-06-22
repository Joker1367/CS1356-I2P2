#include<stdio.h>

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

void insert(Node** node, char c){
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->character =  c;
	
	if((*node) == tail){
		new_node->ptr_to_next_node = head;
		head->prev = new_node;
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
}

void deletion(Node** node){
	if((*node) == tail){
		return;
	}
	Node* del_node = (*node)->ptr_to_next_node;
	(*node)->ptr_to_next_node = (*node)->ptr_to_next_node->ptr_to_next_node;
	(*node)->ptr_to_next_node->ptr_to_prev_node = *node;
	free(del_node);
}

void backspace(Node** node){
	if((*node) == head){
		return;
	}
	Node* del_node = (*node)->ptr_to_prev_node;
	(*node)->ptr_to_prev_node = (*node)->ptr_to_prev_node->ptr_to_prev_node;
	(*node)->ptr_to_prev_node->ptr_to_next_node = *node;
	free(del_node);
}

void go_left(Node** node, int index){
	
}
