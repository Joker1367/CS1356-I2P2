#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct t_List {
 int id;
 char str[10];
 struct t_List* next;
} List;

List* getData(void);
List* addToLast(List* head, List* np);
List* removeFirst(List* head);
void showList(List* lst);
List* freeList(List* lst);

int main(void)
{
 	List* head = NULL;
 	List* np = NULL;
 	while((np = getData()) != NULL) {
 		head = addToLast(head, np);
		showList(head);
	}
	showList(head);
	head = removeFirst(head);
	showList(head);
	head = freeList(head);
	return 0;
}

List* getData(void){
	List* np;
	static int ID;
	
	np = (List*)malloc(sizeof(List));
	if(np != NULL){ // no sufficient memory
		printf("Enter a name: ");
		if(scanf("%9s", np->str) == 1){
			np->id = ID++;
			np->next = NULL;
		}
		else{
			free(np);
			np = NULL;
		}
	}
	return np;
}

List* addToLast(List* head, List* np){
	List* ptr = head;
	if(head == NULL){
		head = np;
	}
	else{
		while(ptr->next != NULL){
			ptr = ptr->next;
		}
		ptr->next = np;
	}
	
	return head;
}

List* removeFirst(List* head){
	List* ptr;
	if(head == NULL){
		return NULL;
	}
	else{
		ptr = head->next;
		free(head);
		return ptr; 
	}
}

void showList(List* head){
	printf("[");
	while(head != NULL){
		printf("%d:%s,", head->id, head->str);
		head = head->next;
	}
	printf("]\n");
}

List* freeList(List* head){
	while(head != NULL){
		head = removeFirst(head);
	}
	return NULL;
}
