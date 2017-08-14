//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"



// private types --------------------------------------------------------------




// NodeObj
typedef struct NodeObj {
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// constructor of the Node type
Node newNode(int data) {
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN) {
	if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// ListObj
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int cursorIndex;
} ListObj;



// public functions -----------------------------------------------------------




// newList()
// constructor for the List type
List newList(void) {
	List L = malloc(sizeof(ListObj));
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->cursorIndex = -1;
	return(L);
}

// freeList()
// destructor for the List type
void freeList(List* pL) {
	if(pL!=NULL && *pL!=NULL) {
		clear(*pL); 
	}
	free(*pL);
	*pL = NULL;
}

// length()
// Returns the number of elements in the List
// pre: none
int length(List L) {
	if(L==NULL) {
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	else {
		return L->length;
	}
}

// index()
// returns the index of the cursor element
// pre: cursor is defined
int index(List L) {
	if(L==NULL) {
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	else {
		return L->cursorIndex;
	}
}

// front()
// returns front element of List
// pre: length()>0
int front(List L) {
	if(L==NULL) {
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
	}
	else {
		if(length(L)>0) {
			return L->front->data;
		}
		else {
			printf("List Error: calling front() on empty List\n");
			exit(1);
		}
	}
}

// back()
// returns back element of List
// pre: length()>0
int back(List L) {
	if(L==NULL) {
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
	}
	else {
		if(length(L)>0) {
			return L->back->data;
		}
		else {
			printf("List Error: calling back() on empty List\n");
			exit(1);
		}
	}
}

// get()
// returns cursor element
// pre: length()>0 && index()>=0
int get(List L) {
	if(L==NULL) {
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}
	else {
		if( length(L)>0 && index(L)>=0) {
			return L->cursor->data;
		}
		else {
			printf("List Error: calling get() on empty List or cursor is undefined\n");
			exit(1);
		}
	}
}

// equals()
// returns true if this List and L are the same integer sequence
// pre: none
int equals(List A, List B) {
	if(A==NULL || B==NULL) {
		printf("List Error: calling equals() on NULL List reference\n");
		exit(1);
	}
	else {
		int true=1;
		int false=0;
		Node Aref = NULL;
		Node Bref = NULL;
		moveFront(A);
		moveFront(B);
		if( length(A) == length(B) ) {
			Aref = A->cursor;
			Bref = B->cursor;
			for(int i=0; i<length(A);i++) {
				if(Aref->data != Bref->data) {
					return false;
				}
				Aref = Aref->next;
				Bref = Bref->next;
			}
			return true;
		}
		return false;
	}
}

// clear()
// resets this List to its original empty state
// pre: none
void clear(List L) {
	if(L==NULL) {
		printf("List Error: calling clear() on NULL List reference\n");
		exit(1);
	}
	else {
		while( length(L) > 0 ) {
			deleteFront(L);
		}
		L->front = NULL;
		L->back = NULL;
		L->cursor = NULL;
		L->length = 0;
		L->cursorIndex = -1;
	}
}

// moveFront()
// places cursor under front element of List
// pre: length()>0
void moveFront(List L) {
	if(L==NULL) {
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(1);
	}
	else {
		if( length(L)>0 ) {
			L->cursor = NULL;
			L->cursor = L->front;
			L->cursorIndex = 0;
		}
		else {
			printf("List Error: calling moveFront() on empty List\n");
			exit(1);
		}
	}
}

// moveBack()
// places cursor under the back element of List
// pre: length()>0
void moveBack(List L) {
	if(L==NULL) {
		printf("List Error: calling moveBack() on NULL List reference\n");
		exit(1);
	}
	else {
		if( length(L)>0 ) {
			L->cursor = NULL;
			L->cursor = L->back;
			L->cursorIndex = length(L)-1;
		}
		else {
			printf("List Error: calling moveBack() on empty List\n");
			exit(1);
		}
	}
}

// movePrev()
// moves cursor one step toward front of List
// unless cursor is undefined or at front of List
// pre: none
void movePrev(List L) {
	if(L==NULL) {
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(1);
	}
	else {
		if( index(L) == -1 ) {}
		else if(index(L) == 0) {
			L->cursor = NULL;
			L->cursorIndex = -1;
		}
		else {
			L->cursor = L->cursor->prev;
			L->cursorIndex--;
		}
	}
}

// moveNext()
// moves cursor one step toward back of List
// unless cursor is undefined or at back of List
// pre: none
void moveNext(List L) {
	if(L==NULL) {
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(1);
	}
	else {
		if( index(L) == -1 ) {}
		else if(index(L) == length(L)-1) {
			L->cursor = NULL;
			L->cursorIndex = -1;
		}
		else {
			L->cursor = L->cursor->next;
			L->cursorIndex++;
		}
	}
}

// prepend()
// inserts new element at front of List
// if List is empty, becomes first element in List 
// pre: none
void prepend(List L, int data) {
	if(L==NULL) {
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(1);
	}
	else {
		Node N = newNode(data);
		if(length(L) == 0) {
			L->front = N;
			L->back = N;
		}
		else {
			Node temp = L->front;
			N->next = temp;
			temp->prev = N;
			L->front = N;
			N->prev = NULL;
			if( index(L) >= 0 ) {
				L->cursorIndex++;
			}
		}
		L->length++;
	}
}

// append()
// inserts new element at back of List
// if List is empty, becomes first element in List 
// pre: none
void append(List L, int data) {
	if(L==NULL) {
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
	}
	else {
		Node N = newNode(data);
		if(length(L)==0) {
			L->front = N;
			L->back = N;
		}
		else {
			Node temp = L->back;
			N->prev = temp;
			temp->next = N;
			L->back = N;
			N->next = NULL;
		}
		L->length++;
	}
}

// insertBefore()
// inserts new element before cursor
// pre: length()>0 && index()>=0
void insertBefore(List L, int data) {
	if(L==NULL) {
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(1);
	}
	else {
		if(length(L)>0 && index(L)>=0) {
			Node N = newNode(data);
			if(L->cursor->prev != NULL) {
				Node temp = L->cursor->prev;
				temp->next = N;
				N->prev = temp;
				N->next = L->cursor;
				L->cursor->prev = N;
			}
			else {
				Node temp = L->front;
				N->next = temp; 
				temp->prev = N;
				L->front = N;
			}
			L->cursorIndex++;
			L->length++;
		}
		else {
			printf("List Error: calling insertBefore() on empty List or cursor is undefined\n");
			exit(1);
		}
	}
}

// insertAfter()
// inserts new element after cursor
// pre: length()>0 && index()>=0
void insertAfter(List L, int data) {
	if(L==NULL) {
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(1);
	}
	else {
		if(length(L)>0 && index(L)>=0 ) {
			Node N = newNode(data);
			if(L->cursor->next != NULL) {
				Node temp = L->cursor->next;
				N->next = temp;
				L->cursor->next = N;
				temp->prev = N;
				N->prev = L->cursor;
			}
			else {
				L->cursor->next = N;
				N->prev = L->cursor;
				N->next = NULL;
			}
			L->length++;
		}
		else {
			printf("List Error: calling insertAfter() on empty List or cursor is undefined\n");
			exit(1);
		}
	}
}

// deleteFront()
// deletes the front element 
// pre: length()>0
void deleteFront(List L) {
	if(L==NULL) {
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	else {
		if( length(L)>0 ) {
			Node temp = L->front;
			L->front = L->front->next;
			freeNode(&temp);
			if(index(L)== 0) {
				L->cursor=NULL;
				L->cursorIndex=-1;
			}
			L->length--;
		}
		else {
			printf("List Error: calling deleteFront() on empty List\n");
			exit(1);
		}
	}
}

// deleteBack()
// deletes the back element
// pre: length()>0
void deleteBack(List L) {
	if(L==NULL) {
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(1);
	}
	else {
		if(length(L)==1) {
			clear(L);
		}
		else if( length(L)>0 ) {
			Node temp = L->back;
			L->back = L->back->prev;
			L->back->next = NULL;
			freeNode(&temp);
			L->length--;
			if(index(L)== length(L)-1) {
				L->cursor=NULL;
				L->cursorIndex = -1;
			}
		}
		else {
			printf("List Error: calling deleteBack() on empty List\n");
			exit(1);
		}
	}
}

// delete()
// deletes cursor element, making cursor undefined
// pre: length()>0 && index()>=0
void delete(List L) {
	if(L==NULL) {
		printf("List Error: calling delete() on NULL List reference\n");
		exit(1);
	}
	else {
		if( length(L)>0 && index(L)>=0 ) {
			if(length(L)==1) {
				clear(L);
			}
			else if(index(L) == length(L)-1) {
				deleteBack(L);
			}
			else if(index(L) == 0) {
				deleteFront(L);
			}
			else {
				Node deletedNode = L->cursor;
				Node temp = L->cursor->prev;
				Node temp2 = L->cursor->next;
				
				temp->next = NULL;
				temp2->prev = NULL;
				temp->next = temp2;
				temp2->prev = temp;
				
				L->cursor = NULL;
				L->cursorIndex = -1;
				L->length--;
				freeNode(&deletedNode);
			}
		}
		else {
			printf("List Error: calling delete() on empty List or cursor is undefined\n");
			exit(1);
		}
	}
}

// printList()
// prints List to out file
// pre: none
void printList(FILE* out, List L) {
	if(L==NULL) {
		//printf("List Error: calling printList() on NULL List reference\n");
		//exit(1);
	}
	else {
		Node N = L->front;
		while( N != NULL ) {
			fprintf(out, "%s", " ");
			fprintf(out, "%d", N->data);
			N = N->next;
		}
	}
}

// copyList()
// returns a new List representing the same integer sequence as this List
// pre: none
List copyList(List L) {
	if(L==NULL) {
		printf("List Error: calling copyList() on NULL List reference\n");
		exit(1);
	}
	else {
		List returnList = newList();
		Node N = L->front;
		for(int i=0; i<length(L); i++) {
			append(returnList,N->data);
			N=N->next;
		}
		return returnList;
	}
}

// concatList()
// returns a new List which is the concatenation of this list followed by L
// pre: none
List concatList(List A, List B) {
	if(A==NULL || B==NULL) {
		printf("List Error: calling concatList() on NULL List reference\n");
		exit(1);
	}
	else {
		List returnList = newList();
		Node Anode = A->front;
		for(int i=0; i<length(A); i++) {
			append(returnList, Anode->data);
			Anode = Anode->next;
		}
		Node Bnode = B->front;
		for(int i=0; i<length(B); i++) {
			append(returnList, Bnode->data);
			Bnode = Bnode->next;
		}
		return returnList;
	}
}
