#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cirListDeq.h"

/*
	initCirListDeque: Initialize deque.
	param: 	q pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void initCirListDeque (struct cirListDeque *q) {
	/* FIX ME*/
    struct DLink* lnk = (struct DLink*)malloc(sizeof(struct DLink));
    assert(lnk != 0);   //sentinel made
    q->Sentinel = lnk;
    q->Sentinel->next = q->Sentinel->prev = q->Sentinel;
    q->size = 0;

    return;
}

/*
 create a new circular list deque
 */
struct cirListDeque *createCirListDeque()
{
    struct cirListDeque* newCL = malloc(sizeof(struct cirListDeque));
    initCirListDeque(newCL);

    return(newCL);
}

/* Create a link for a value.

    param:  val the value to create a link for
    pre:    none
    post:   a link to store the value
*/
struct DLink * _createLink (TYPE val){
    struct DLink* lnk = (struct DLink*) malloc(sizeof(struct DLink));
    lnk->value = val;

    return(lnk);
}

/* Adds a link after another link

    param:  q   pointer to the deque
    param:  lnk  pointer to the existing link in the deque
    param:  newLnk  pointer to the new link to add after the existing link
    pre:    q is not null
    pre:    lnk and newLnk are not null
    post:   the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk){
    lnk->next->prev = newLnk;       //right connects to new
    newLnk->next = lnk->next;       //new connect to right
    newLnk->prev = lnk;             //new connect to left
    lnk->next = newLnk;             //left connect to new
    q->size++;

    return;
}
/*
	addBackCirListDeque:
	Adds a link to the back of the deque
	param: 	q pointer to the deque
	param: 	val	value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) {
	struct DLink* lnk = _createLink(val);
    _addLinkAfter(q, q->Sentinel->prev, lnk);

    return;
}

/*
	addFrontCirListDeque: Adds a link to the front of the deque
	param: 	q pointer to the deque
	param: 	val	value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val) {
	struct DLink* lnk = _createLink(val);
    _addLinkAfter(q, q->Sentinel, lnk);

    return;
}

/*
	frontCirListDeque: Get the value of the front of the deque
	param: 	q pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) {
	return q->Sentinel->next->value;
}

/*
	backCirListDeque: Get the value of the back of the deque
	param: 	q pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q) {
	return q->Sentinel->prev->value;
}

/* Remove a link from the deque

    param:  q       pointer to the deque
    param:  lnk     pointer to the link to be removed
    pre:    q is not null and q is not empty
    post:   the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk){
    //assert(!isEmptyList(lst));
    lnk->next->prev = lnk->prev;    //connect right link to left link
    lnk->prev->next = lnk->next;    //connect left link to right link
    q->size--;
    free(lnk);

    return;
}

/*
	removeFrontCirListDeque: Remove the front of the deque
	param: 	q pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
	_removeLink(q, q->Sentinel->next);

	return;
}


/*
	removeBackCirListDeque: Remove the back of the deque
	param: 	q pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q) {
	_removeLink(q, q->Sentinel->prev);

	return;
}

/*
	isEmptyCirListDeque: Check whether the deque is empty
	param: 	q pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
	return q->size == 0;
}

/*
	printCirListDeque: Print the links in the deque from front to back
	param: 	q pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q) {
	struct DLink *current;
    int x = 0;
    assert(!isEmptyCirListDeque(q));

    current = q->Sentinel->next;
    while(current != q->Sentinel){
        printf("value: %f\t\n", current->value);
        current = current->next;
        x++;
        if (x >= 6){li
            printf("\n");
            x = 0;
        }
    }
}

/*
	freeCirListDeque: De-allocate all links of the deque
	param: 	q pointer to the deque
	pre:	none
	post:	All links (including backSentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q) {
	while (q->size > 0){
        removeFrontCirListDeque(q);
    }
    free(q->Sentinel);
}
