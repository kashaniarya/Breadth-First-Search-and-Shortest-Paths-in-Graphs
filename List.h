//-----------------------------------------------------------------------------
// List.h
// Header file for the List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// List
// Exported reference type
typedef struct ListObj* List;

// newList()
// constructor for the List type
List newList(void);

// freeList()
// destructor for the List type
void freeList(List* pL);

// length()
// Returns the number of elements in the List
// pre: none
int length(List L);

// index()
// returns the index of the cursor element
// pre: cursor is defined
int index(List L);

// front()
// returns front element of List
// pre: length()>0
int front(List L);

// back()
// returns back element of List
// pre: length()>0
int back(List L);

// get()
// returns cursor element
// pre: length()>0 && index()>=0
int get(List L);

// equals()
// returns true if this List and L are the same integer sequence
// pre: none
int equals(List A, List B);

// clear()
// resets this List to its original empty state
// pre: none
void clear(List L);

// moveFront()
// places cursor under front element of List
// pre: length()>0
void moveFront(List L);

// moveBack()
// places cursor under the back element of List
// pre: length()>0
void moveBack(List L);

// movePrev()
// moves cursor one step toward front of List
// unless cursor is undefined or at front of List
// pre: none
void movePrev(List L);

// moveNext()
// moves cursor one step toward back of List
// unless cursor is undefined or at back of List
// pre: none
void moveNext(List L);

// prepend()
// inserts new element at front of List
// if List is empty, becomes first element in List 
// pre: none
void prepend(List L, int data);

// append()
// inserts new element at back of List
// if List is empty, becomes first element in List 
// pre: none
void append(List L, int data);

// insertBefore()
// inserts new element before cursor
// pre: length()>0 && index()>=0
void insertBefore(List L, int data);

// insertAfter()
// inserts new element after cursor
// pre: length()>0 && index()>=0
void insertAfter(List L, int data);

// deleteFront()
// deletes the front element 
// pre: length()>0
void deleteFront(List L);

// deleteBack()
// deletes the back element
// pre: length()>0
void deleteBack(List L);

// delete()
// deletes cursor element, making cursor undefined
// pre: length()>0 && index()>=0
void delete(List L);

// printList()
// prints List to out file
// pre: none
void printList(FILE* out, List L);

// copyList()
// returns a new List representing the same integer sequence as this List
// pre: none
List copyList(List L);

// concatList()
// returns a new List which is the concatenation of this list followed by L
// pre: none
List concatList(List A, List B);

#endif





