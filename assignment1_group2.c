/*
 * This program implements a singly linked list to store integers.
 * The following functions can be performed on the linked list:
 *
 *     addFirst
 * 	   addLast
 *     add
 *     printList
 *     search
 *     removeFirst
 *     removeLast
 *     mergeSortedLists
 *
 * This program also implements a command line interface that allows
 * the user to access the first seven of these eight functions to create
 * and manipulate a linked list.
 * 
 * This program was created by:
 *
 *     Ana Aguiar Azambuja
 *     Elizabeth Gardner
 *     Megumi Shirasaki
 *     Katie Wilson-Maher
 */

#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node *next;
}; // node

struct linkedList{
	struct node *head;
	struct node *tail;
	int length;
}; // linkedList


// This function takes no input and creates/returns an empty linked list
// (head and tail pointer point to NULL).
struct linkedList* createLinkedList(){
	struct linkedList* newLinkedList = (struct linkedList*)malloc(sizeof(struct linkedList));
	newLinkedList->head = NULL;
	newLinkedList->tail = NULL;
	newLinkedList->length = 0;
	return newLinkedList;
} // createLinkedList()


// This function takes an integer data and creates/returns a node with it.
struct node* createNode(int data){
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
} // createNode()


// This function takes a singly linked list and an integer e,
// and adds a node containing e at the beginning of the linked list.
// It appropriately updates the head, tail, and length of the list.
void addFirst(struct linkedList* list, int e){
	struct node *newNode = createNode(e);
	if(list->head == NULL){
		list->tail = newNode;
	}
	newNode->next = list->head;
	list->head = newNode;
	list->length++;
} // addFirst()


// This function takes a singly linked list and an integer e,
// and adds a node containing e at the end of the linked list.
// It appropriately updates the head, tail, and length of the list.
void addLast(struct linkedList* list, int e){
	struct node* newNode = createNode(e);
	if(list->tail == NULL){
		list->head = newNode;
	}
	else{
		list->tail->next = newNode;
	}
	list->tail = newNode;
	list->length++;
} // addLast()


// This function takes a singly linked list and an integer index
// and returns a node with the given index.
struct node* getNode(struct linkedList* list, int index){
	struct node* currentNode = list->head;
	for(int currentIndex = 0; currentIndex < index - 1; currentIndex++){
		currentNode = currentNode->next;
	}
	return currentNode;
} // getNode()

// This function takes a singly linked list, an integer e,
// and an integer pos. This function creates a node with integer e
// and inserts the new node at position pos in the linked list.
void add(struct linkedList* list, int e, int pos){
	if(pos < 0 || pos > list->length){
		printf("Invalid position\n");
		int newPos;
		printf("\nEnter new position: ");
		scanf("%d", &newPos);
		add(list, e, newPos);
	}
	else if(pos == 0){
		addFirst(list, e);
	}
	else if(pos == list->length){
		addLast(list, e);
	}
	else{
		struct node* newNode = createNode(e);
		struct node* currentNode = getNode(list, pos);
		newNode->next = currentNode->next;
		currentNode->next = newNode;
		list->length++;
	}
} // add()


// This function takes a singly linked list and prints the data stored
// in each element of the linked list.
void printList(struct linkedList* list){
	struct node* currentNode = list->head;
	if(currentNode != NULL){
		printf("%d", currentNode->data);
		currentNode = currentNode->next;
	}
	while(currentNode != NULL){
		printf(", %d", currentNode->data);
		currentNode = currentNode->next; 
	}
	printf("\n");
} // printList()


// This function takes a singly linked list and an integer key.
// It returns the first node in the linked list containing the
// integer key. If the linked list does not contain the key, it will return NULL.
struct node* search(struct linkedList* list, int key){
	struct node* currentNode = list->head;
	while(currentNode != NULL && currentNode->data != key){
		currentNode = currentNode->next;
	}
	return currentNode;
} // search()


// This function takes a singly linked list and removes and returns
// the first node in the linked list. // It appropriately updates
// the head, tail, and length of the list.
struct node* removeFirst(struct linkedList* list){
	struct node* oldHead = list->head;
	if(oldHead == NULL){
		printf("\nThe list is empty\n");
		return NULL;
	}
	list->head = list->head->next;
	list->length--;
	return oldHead;
} // removeFirst()


// This function takes a singly linked list and removes and returns
// the last node in the linked list. // It appropriately updates
// the head, tail, and length of the list.
struct node* removeLast(struct linkedList* list){
	struct node* currentNode = list->head;
	if(currentNode == NULL){
		printf("\nThe list is empty\n");
		return NULL;
	}
	while(currentNode->next->next != NULL){
		currentNode = currentNode->next;
	}
	list->tail = currentNode;
	struct node* tempNode = currentNode->next;
	currentNode->next = NULL;
	list->length--;
	return tempNode;
} // removeLast()

// This function takes two sorted linked lists and merges them into a
// single sorted linked list.
struct linkedList* mergeSortedLists(struct linkedList* list1, struct linkedList* list2){
	struct linkedList* newLinkedList = createLinkedList();
	struct node* list1Node = list1->head;
	struct node* list2Node = list2->head;
	while(list1Node != NULL && list2Node != NULL){
		if(list1Node->data <= list2Node->data){
			addLast(newLinkedList, list1Node->data);
			list1Node = list1Node->next;
		}
		else{
			addLast(newLinkedList, list2Node->data);
			list2Node = list2Node->next;
		}	
	}
	while(list1Node != NULL){
		addLast(newLinkedList, list1Node->data);
		list1Node = list1Node->next;
	}
	while(list2Node != NULL){
		addLast(newLinkedList, list2Node->data);
		list2Node = list2Node->next;
	}
	return newLinkedList;
} // mergeSortedLists()

// The main function implements the command line interface, which allows
// the user to access the addFirst, addLast, add, printList, search,
// removeFirst, and removeLast functions to create and manipulate a
// linked list from the terminal.
int main(){

    struct linkedList* list = createLinkedList();
    
    int opt;
    while(opt != 8){
    
		printf("\nChoose an option:\n1. Add at the beginning\n2. Add at the end\n3. Add at a position\n4. Print the list\n5. Search the list\n6. Remove the first item\n7. Remove the last item\n8. Quit\n\nOption: ");
		scanf("%d", &opt);
		
		if(opt == 1){
			// addFirst
			int e;
			printf("\nEnter data: ");
			scanf("%d", &e);
			addFirst(list, e);
		}
		else if(opt == 2){
			// addLast
			int e;
			printf("\nEnter data: ");
			scanf("%d", &e);
			addLast(list, e);
		}
		else if(opt == 3){
			// add
			int e;
			int pos;
			printf("\nEnter data: ");
			scanf("%d", &e);
			printf("\nEnter position: ");
			scanf("%d", &pos);
			add(list, e, pos);
		}
		else if(opt == 4){
			// printList
			printf("\nLinked List: ");
			printList(list);
		}
		else if(opt == 5){
			// search
			int key;
			printf("\nEnter key: ");
			scanf("%d", &key);
			struct node *foundNode = search(list, key);
			if(foundNode != NULL){
				printf("\nFound node\n");
			}
			else{
				printf("\nNode not found\n");
			}
		}
		else if(opt == 6){
			//removeFirst
			removeFirst(list);
		}
		else if(opt == 7){
			//removeLast
			removeLast(list);
		}
		else if(opt == 8){
			// quit
			printf("\nQuitting\n");
		}
		else{
			//invalid input
			printf("\nInvalid input\n");
		}
		
	}
		
} // main()
