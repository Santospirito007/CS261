#include <stdio.h>
#include <stdlib.h>

#define TYPE double

struct node{
    TYPE value;
    struct node *next;
};

void insertBeg(struct node *head, TYPE x){
    struct node *temp = malloc(sizeof(struct node));
    temp->value = x;
    temp->next = head->next;
    head->next=temp;

    printf("added %f\n", x);

    return;
}

void insertEnd(struct node *head, TYPE x){
    struct node *temp, *curr;
    temp=malloc(sizeof(struct node));
    curr=head;

    while(curr->next != NULL){
        curr=curr->next;
    }

    temp->next = NULL;
    curr->next = temp;
    temp-> value=x;

    printf("inserted %f to end\n", x);

    return;
}

void insertAtIndex(struct node *head, TYPE x, int pos){
    struct node *temp, *curr;
    int i =0;
    temp=malloc(sizeof(struct node));
    curr=head;

    if(pos!=-1){
        while(i<pos&&curr->next !=NULL){
            curr=curr->next;
            i++;
        }
    } else{
        while(curr->next!=NULL){
            curr=curr->next;
        }
    }

    temp->next = curr->next;
    curr->next = temp;
    temp->value =x;

    printf("inserted %f at index %d \n", x, pos);

    return;
}

void deleteAtIndex(struct node *head, int pos){
    struct node *curr, *next;
    curr = head;
    int i=0;

    while(i < pos && curr->next->next != NULL){
        curr = curr->next;
        i++;
    }

    next=curr->next;
    curr->next=curr->next->next;
    free(next);

    printf("deleted %d\n", pos);

    return;
}

void printList(struct node * head){
    struct node *curr=head;
    int i=0;
    while(curr->next != NULL){
        curr= curr->next;
        printf("item %d: %f\n", i, curr->value);
        i++;
    }

    return;
}


/******* main below this********/
int main(){

    struct node *head=0;
    head = malloc(sizeof(struct node));
    head->next =NULL;

    insertBeg(head, 5);
    insertBeg(head, 10);
    insertBeg(head, 15);

    insertEnd(head, 100);

    insertAtIndex(head, 6, 0);
    insertAtIndex(head, 500, -1);

    printList(head);

    deleteAtIndex(head, 99);

    printList(head);

    return 0;
}
