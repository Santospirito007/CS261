/*
    skip list implementation
    link heights are probabilistically determined
    link heights are only allowed to exceed current max (currMax) height by one
    link heights are capped at maximum level (maxLevel)
*/

#include "skipList.h"
#include <malloc.h>

/*
    initSkipList: Skiplist is initialized
    pre: list is not null
    pre: max is at least 1 max. should be set to log n of the number of level 1 links
    param1: list - the list
    param2: max - maximum depth of the list
    post: memory is allocated to sentinel
    maxLevel, currMax and size are initialized
*/
void initSkipList(struct skipList *list, int max) {
    int i;
    assert(list != NULL);
    assert(max > 0);
    list->sentinel = malloc(sizeof(struct sLink)+sizeof(struct sLink)*max);/* sentinel is an array with a pointer to every level */
    list->maxLevel = max;/* max allowable levels */
    list->currMax = 0;/* level of highest node currently */
    list->size = 0;/* number of level 1 links */


    for(i = max; i > 0; i--) {
        list->sentinel->next[i] = list->sentinel;/* sentinel points to itself at every level */
    }

    return;
}

/*
    levelGen: Generate a random level for new links
    pre: list is not null
    param1: list - the list
    return: random level
    post: random level cannot exceed list->maxLevel
        _random level can only exceed currMax by 1

    random levels are determined by a "series of coin flips"
    Each level is 50% less common than the last
    Approximately 50% are level 2, 25% are level 3, 12.5% are level 4, etc
    Each consecutive "heads" adds one to the level, at the first "tails"
        _we have reached our level
    start at level 1 and add 1 for each heads
    Ex: HHT = level 3, T = 1, THH = 1, HHHT = 4
*/
int levelGen(struct skipList *list) {
    /* FIX ME */
    int randLvl = 1;
    while (rand() < RAND_MAX/2 && randLvl < list->maxLevel){
        randLvl++;
    }


    //if's below max sure to meet post return statements
    if(randLvl > list->maxLevel){
        randLvl = list->maxLevel;
    }
    if(randLvl > list->currMax){
        randLvl = (list->currMax+1);
    }

	/* FIX ME */
    return randLvl;
}

/*
    addValTest: Adds a value to the skipList at a specified - useful for testing purposes
    pre: list is not null
    pre: lvl > 0 and lvl <= maxLevel
    param1: list - the list
    param2: val - the value to add
    param3: lvl - the level of the link
    post: value is added to the skip list at each necessary level
*/


void addValTest(struct skipList *list, TYPE val, int lvl) {
    assert(list != NULL);
    assert(lvl <= list->maxLevel && lvl > 0);

    /* pointers for node to insert and iterator node */
    struct sLink *insert, *curr;
    /* allocate memory for link to insert -
        _extra space is allocated for the "height" of the link */
    insert = malloc(sizeof(struct sLink) + sizeof(struct sLink)*lvl);
    /* FIX ME */
    /* HINT - this is simply a test function - don't hesitate to put debugging statements in to help navigate */
    /* set insert value to val */
    insert->value=val;
    /* set insert level to level */
    insert->level=lvl;
    /* if lvl is greater than currMax, set currMax to lvl */
    if(lvl>list->currMax){
        list->currMax = lvl;
    }
    /* initialize curr to sentinel */
    curr = list->sentinel;
    /* add insert to the correct position for each level
        _of the skip list less or equal to the link's level */
    /* HINT - start at the top and work down */
    int i = lvl;
    while(i>0){
        while(curr->next[i]!= list->sentinel && curr->next[i]->value < val){
            curr=curr->next[i];
           // printf("slide right\n"); //debug: it slid right 1
        }

        insert->next[i] = curr->next[i];
        curr->next[i] = insert;
        printf("inserted %d at: %d\n", val, i);

        i--;

        //printf("slid down\n");//debug: it level slid down 1
    }

    list->size++;

    return;
}

/*
    addVal: Adds a value to the skipList at a random level
    pre: list is not null
    pre: lvl > 0 and lvl <= maxLevel
    param1: list - the list
    param2: val - the value to add
    post: value is added to the skip list at each necessary level.
        _Level is generated randomly.
*/
void addVal(struct skipList *list, TYPE val) {
	/* FIX ME */
	int getLevel;
	int i;
	assert(list!=NULL);

	getLevel = levelGen(list);
	assert(getLevel >0 && getLevel <= list->maxLevel);

	struct sLink *insert, *curr;
	insert = malloc(sizeof(struct sLink) + sizeof(struct sLink)*getLevel);

    //setting the correct values to their places
	insert->value=val;
    insert->level=getLevel;

    //setting currMax to the new level height
    if(getLevel > list->currMax){
        list->currMax = getLevel;
    }

    curr = list->sentinel;

    i=getLevel; //this will be used to make sure to add all the levels correctly

    while(i>0){
        while(curr->next[i]!= list->sentinel && curr->next[i]->value < val){
            curr=curr->next[i];
           // printf("slide right: addVal function\n"); //debug: it slid right 1
        }

        insert->next[i] = curr->next[i];
        curr->next[i] = insert;
        printf("inserted %d at: %d  in addVal\n", val, i);

        i--;

        //printf("slid down: addVal function\n");//debug: it level slid down 1
    }

    list->size++;

	/* HINT - this is the same process as addValTest
        _with one exception. You need to generate a level using LevelGen() */

    return;
}

/*
    searchVal: Searches the skipList for a value
    pre: list is not null
    param1: list - the list
    param2: val - the search value
    post: returns the number of comparisons needed
        _to find the value - If not found, return 0
*/
int searchVal(struct skipList *list, TYPE val) {
	/* FIX ME */
	struct sLink *curr = list->sentinel;
    int i;
    int comparisons = 0;

    assert(list!=NULL);

    for (i = list->currMax; i >= 1; i--) {
        while (curr->next[i]!= list->sentinel && curr->next[i]->value < val){
            curr = curr->next[i];
            comparisons++;
        }
    }

    if (curr->next[1]->value == val) {
        comparisons++;
    } else {
        comparisons = 0;
    }

    return comparisons;
}



/*
    printLv: Print the specified level of the list
    pre: list is not null
    pre: lv is greater than 0 and less than list->maxLevel
    param1: list - the list
    param2: lv - level of the list to print
    post: prints all of the values at a specified level
*/
void printLv(struct skipList *list, int lv) {
	/* FIX ME */
	assert(list!= NULL);
	assert(lv>0 && lv<= list->maxLevel);

	struct sLink *temp;
	temp = list->sentinel;
	//printf("i got here 2\n");//making sure function got here

	while(temp->next[lv]!= list->sentinel){
        printf("%d\n", temp->next[lv]->value);
        temp=temp->next[lv];
	}


    printf("End of printVal on level: %d\n", lv);

    return;
}

/*
    getSize: return the number of level 1 links in the skip list
    pre: list is not null
    param1: list - the list
    post: return the number of level 1 links in the list
*/
int getSize(struct skipList *list) {
	/* FIX ME */
	int counter =0;
    assert(list!=NULL);

	struct sLink *curr;
	curr=list->sentinel;

	while(curr->next[1]!= list->sentinel){
        curr= curr->next[1];
        counter++;
	}

	return counter;
}

/*
    removeLink: Remove the first instance of the link containing
        _the value from the list
    pre: list is not null
    param1: list - the list
    param2: val - value to remove
    post: link is removed from the list and pointers are adjusted
    post: if not found "Not Found" is displayed via standard output
*/
void removeLink(struct skipList *list, TYPE val) {
    int i;
	int maxLevel;
	int check = 0;

	assert(list!=NULL);

	maxLevel = list->currMax;

	struct sLink *curr, *temp;


    //setting currMax to the new level height

    curr = list->sentinel;

    i=maxLevel; //this will be used to make sure to start at the top.

    while(i>0){
        while(curr->next[i]!= list->sentinel && curr->next[i]->value < val){
            curr=curr->next[i];
           // printf("slide right: addVal function\n"); //debug: it slid right 1
        }

        if(curr->next[i]->value == val){

            temp = curr->next[i];
            curr->next[i] =curr->next[i]->next[i];


            check = 1;
        }


        i--;

        //printf("slid down: addVal function\n");//debug: it level slid down 1
    }

    if(check == 1){
       // printf("Value found.\n");;
       free(temp);
    }
    else{
        printf("Value not found.\n");
    }

    list->size--;

	return;

}

/*
    deleteList: delete all links from the list as well as the list
    pre: list is not null
    param1: list - the list
    post: all links are deallocated
    post: list is deallocated
*/
void deleteList(struct skipList *list) {
	/* FIX ME */

	struct sLink *current_node = list->sentinel->next[1];
    while(current_node != list->sentinel) {
        struct sLink *next_node = current_node->next[1];
        free(current_node->next);
        free(current_node);
        current_node = next_node;
    }
    free(list->sentinel);
    free(list);

	return;
}
