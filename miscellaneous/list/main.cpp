#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

/*	
	  A C-style list
*/

typedef struct node
{
	int data;
	struct node *next;
	struct node *prev;
}Node;

typedef struct list
{
	Node *hdr;
	Node *tail;
	void (*push_back)(int);
	void (*push_front)(int);
	void (*pop_back)();
	void (*pop_front)();
	void (*print)();
	void (*print_reverse)();
}List;


List myList;
void initList();

void push_back_node(int value)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	
	if (!newNode) 
		exit(1);

	if (myList.hdr == 0)
		{
			newNode->next = newNode->prev = 0;
			newNode->data = value; 
			myList.tail = myList.hdr = newNode;
		}
	else
		{	
			newNode->data = value;
			newNode->next = 0;
			myList.tail->next = newNode;
			newNode->prev = myList.tail;
			myList.tail = myList.tail->next;
		}
	
}

void push_front_node(int value)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	
	if (!newNode) 
		exit(1);

	if (myList.hdr == 0)
		{
			newNode->next = newNode->prev = 0;
			newNode->data = value;
			myList.hdr  = newNode;
			myList.tail = myList.hdr = newNode;
		}
	else
		{	
			newNode->data = value;
			newNode->prev = 0;
			myList.hdr->prev = newNode;
			newNode->next = myList.hdr;
			myList.hdr = myList.hdr->prev;
		}
}

void pop_back_node()
{
	 
	Node *to_del = 0;

	 if (myList.hdr == 0) return;

	 if (myList.hdr == myList.tail)
		{
			to_del = myList.tail;
			myList.tail = myList.hdr = 0;
		}
	 else
		{
			to_del = myList.tail;
			myList.tail = myList.tail->prev;
			myList.tail->next = 0;
		}
 
	 free((void *)to_del);
	 to_del = 0;
	
}

void pop_front_node()
{
	
	Node *to_del = 0;
	
	 if (myList.hdr == 0) return;

	 if (myList.hdr == myList.tail)
		{	
			to_del = myList.hdr;
			myList.hdr = myList.tail = 0;
		}
	 else
		{
			to_del = myList.hdr;
			myList.hdr = myList.hdr->next;
			myList.hdr->prev = 0;
		}
	 
	 free((void *)to_del);
	 to_del = 0;
	 
}

void printList()
{

	Node *curr = myList.hdr;
	
	while (curr != 0)
		{
			printf("%d\n",curr->data);
			curr = curr->next;
		}
	
	printf("\n");
}

void printListReverse()
{

	Node *curr = myList.tail;
	
	while (curr != 0)
		{
			printf("%d\n",curr->data);
			curr = curr->prev;
		}

	printf("\n");
}

void freeList()
{

	Node *curr = myList.hdr;
	Node *p = 0;

	while (curr != 0)
		{
			p = curr;	
			curr = curr->next;
			free((void *)p);
		}
}


void addAfter()
{
	int str;
	
	printf("Insert a value\n");

	int _r = scanf("%d",&str);
	if (_r != 1) {fflush(stdin); return;}

	myList.push_back(str); 

}

void addBefore()
{
	int str;
	
	printf("Insert a value\n");

	int _r = scanf("%d",&str);
	if (_r != 1) {fflush(stdin); return;}

	myList.push_front(str); 

}

void initList()
{
	myList.hdr = myList.tail = 0;
	myList.push_back = push_back_node;
	myList.push_front = push_front_node;
	myList.pop_back = pop_back_node;
	myList.pop_front = pop_front_node;
	myList.print = printList;
	myList.print_reverse = printListReverse;
}

void writeOutput()
{
	printf("1 - push back\n");
	printf("2 - push front\n");
	printf("3 - pop back\n");
	printf("4 - pop front\n");
}

int main()
{
	
	int choice;
	initList();

	while(1)
		{
			fflush(stdin);
			writeOutput();
			int _r = scanf("%d",&choice);
			if (_r != 1) {fflush(stdin); choice = 0;}
			switch(choice)
				{
					case 1:
							addAfter();	
							myList.print();
							myList.print_reverse();
					break;

					case 2:
							addBefore();
							myList.print();
							myList.print_reverse();
					break;
					
					case 3:
							myList.pop_back(); 
							myList.print();
							myList.print_reverse();
					break;
					
					case 4:
							myList.pop_front();
							myList.print();
							myList.print_reverse();
					break;
				}

		}
	
	freeList();

	return 0;
}


