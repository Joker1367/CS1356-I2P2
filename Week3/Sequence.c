#include<stdio.h>
#include<stdlib.h>

typedef struct _Node{
	int data;
	struct _Node* next;
} Node;

Node* head;
char instruct[100];
int len = 1;

Node* insert(int amt, int num);
void erase(int val);
void move(int val);
void show(void);

Node* insert(int amt, int num){
	if(amt == 0){
		return head->next;
	}
	Node* new_node = (Node*)malloc(sizeof(new_node));
	new_node->data = num;
	new_node->next = insert(amt - 1, num);
	return new_node;
}

void erase(int val){
	Node* cur = head->next;
	Node* prev = head;
	while(val-- && cur != head){
		prev->next = cur->next;
		free(cur);
		cur = prev->next;
	}
}

void move(int val){
	val = val % len;
	while(val--){
		head = head->next;
	}
}

void show(){
	Node* cur = head;
	do{
		printf("%d", cur->data);
		if(cur->next != head){
			printf(" ");
		}
		else{
			printf("\n");
		}
		cur = cur->next;
	}while(cur != head);
}

int main(void){
	int x, n;
	scanf("%d %d", &x, &n);
	head = (Node*)malloc(sizeof(Node));
	head->data = x;
	head->next = head;
	
	while(n--){
		scanf("%s", instruct);
		if(strcmp(instruct, "insert") == 0){
			int val, amt;
			scanf("%d %d", &val, &amt);
			head->next = insert(amt, val);
			len += amt;
		}
		else if(strcmp(instruct, "erase") == 0){
			int amt;
			scanf("%d", &amt);
			erase(amt);
			len -= amt;
		}
		else if(strcmp(instruct, "move") == 0){
			int amt;
			scanf("%d", &amt);
			move(amt);
		}
		else{
			show();
		}
	}
	return 0;
}
