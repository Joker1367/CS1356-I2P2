#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int number;
    struct _Node* next;
}Node;
Node *createList(int n);
void freeList(Node* head);
int solveJosephus(Node **head, int step);

Node* createList(int n){
	Node* head = (Node*)malloc(sizeof(Node));
	head->number = 1;
	head->next = head;
	
	int i;
	Node*  cur = head;
	for(i = 2; i <= n; i++){
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->number = i;
		new_node->next = head;
		cur->next = new_node;
		cur = new_node;
	}
	return head; 
}

void freeList(Node* head){
	/*Node* dummy = (Node*)malloc(sizeof(Node));
	dummy->next = head;
	
	Node* prev = head;
	Node* cur = head->next;
	
	while(cur != head){
		prev->next = cur->next;
		free(cur);
		cur = prev->next;
	}
	free(cur);
	free(dummy);*/
	return;
}

int solveJosephus(Node** head, int step){
	Node* cur = *head;
	Node* prev = *head;
	int len = 1;
	while(prev->next != *head){
		prev = prev->next;
		len++;
	}
	
	while(cur != prev){
		int index = (step % len == 0) ? len : (step % len);
		while(index > 1){
			prev = prev->next;
			cur = cur->next;
			index--;
		}
		prev->next = cur->next;
		free(cur);
		cur = prev->next;
		len--;
	}
	
	int res = cur->number;
	free(cur);
	return res;
}

#endif
