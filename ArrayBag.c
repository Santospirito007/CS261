#include <stdio.h>
#include <stdlib.h>

/*Assume type int
Assume an array is used to
store elements*/
typedef struct bag {
    int size;
    int capacity;
    int *data;
}Bag;



void initBag(struct bag *b, int cap) {
    b->size=0;
    b->capacity=cap;
    b->data=malloc(cap*sizeof(int));
    printf("bag init \n");
}


void displayBag(struct bag *b) {
    int i;
    for(i=0; i<b->size;i++ ){
        printf("index %d: %d\n", i, b->data[i]);
    }

    return;
}

void addBag(struct bag *b, int item) {
    b->data[b->size]=item;
    b->size++;

return;
}

int containsBag(struct bag *b, int item) {
    int i;
    int returnValue=-1;
    for(i=0; i<b->size;i++){
        if(b->data[i]==item){
            returnValue= i;
        }
    }
    return returnValue;
}

void removeBag(struct bag *b, int item){
    int i;
    int pos =containsBag(b, item);
    if(pos!=-1){
        for(i=pos; i< b->size; i++){
            b->data[i] = b->data[i+1];
        }
        b->size--;
    }else{
        printf("Does not contain this item.\n");
    }


    return;
}



int main() {
    struct bag myBag;
    initBag(&myBag, 4);
    addBag(&myBag, 5);
    addBag(&myBag, 11);
    addBag(&myBag, 8);
    displayBag(&myBag);

    printf("search for 777:%d \n",containsBag(&myBag, 777));
    printf("search for 11:%d \n",containsBag(&myBag, 11));

    removeBag(&myBag, 565);
    removeBag(&myBag, 5);

    displayBag(&myBag);




    return 0;
}
