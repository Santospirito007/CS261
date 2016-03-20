#include "hashMap.h"

/********************************************//**
 * \hashFunction1: The first hash function you will use - the sum of the ASCII values is computed
 *
 * \param1: str - the string to hash
 * \pre: str is not NULL
 * \post: none
 * \return: the sum of the ASCII values of the word is returned
 *
 ***********************************************/
int hashFunction1(char *str) {
    /* FIX ME */
    int ascii=0;
    int i;

    for (i = 0; str[i] != '\0'; i++) {
		ascii += str[i];
	}

	return ascii;
}

/*
	hashFunction2: The second hash function you will use - the difference is in the for loop
	param1: str - the string to hash
	pre: str is not NULL
	post: none
	return: the hash is returned - not as easily explained as hashFunction1
*/
int hashFunction2(char *str) {
	int i;
	int h = 0;
	for (i = 0; str[i] != '\0'; i++) {
		h += (i+1) * str[i];
	}
	return abs(h);
}

/*
	hashValue: returns the hash of the key - hash algorithm is specified
	param1: str - the string to hash
	param2: hashNum - the number of the hashing function
	pre: str is not NULL
	post: none
	return: the hash is returned
*/
int _hashValue(char *key, int hashNum) {
    if(hashNum == 1) {
        return hashFunction1(key);
    } else {
        return hashFunction2(key);
    }
}

/*
	initMap: Initialize the hashMap
	param1: ht - the hash map to initialize
	param2: tableSize - the size of the hash map
	pre: ht is not NULL
	pre: tableSize is greater than 0
	post: memory for table has been allocated - need to store specified (tableSize) hash links
	post: tableSize has been set
	post: bucketCount is set to 0
	post: count is set to 0
	post: hashID is set to ID
	post: all hash links (buckets) are initialized to NULL
*/
void _initMap(struct hashMap *ht, int tableSize, int ID) {
	assert(ht != NULL);
	assert(tableSize > 0);

	int i;
    /* malloc table and initialize values */
    ht->tableSize = tableSize;
	ht->count = 0;
	ht->hashID = ID;
	ht->table = malloc(sizeof(struct hashLink) * tableSize);
	ht->bucketCount = 0;

    /* initialize all links to NULL */
    for(i=0; i<tableSize; i++){
        ht->table[i] = NULL;
    }

    return;
}

/*
	createMap: allocate memory and initialize a hash map
	param1: tableSize - the capacity of the table
	pre: tableSize > 0
	return: newly created hash map of size, tableSize
    post: memory for the hash map has been created
    post: hash map of size tableSize has been initialized
*/
struct hashMap *createMap(int tableSize, int ID) {
	assert(tableSize > 0);

	struct hashMap *ht;
	ht = malloc(sizeof(struct hashMap));
	assert(ht != 0); /* ensure that memory was successfully allocated */

	_initMap(ht, tableSize, ID);
	return ht;
}

/*
    _reSizeTable: Resizes the hash map to the size, newCap. Rehashes all of the current keys.
    param1: hashMap - the map
	param2: newCap - the new capacity
	pre: ht is not empty
	pre: newCap is > 0
	post: ht now has tableSize, newCap.
	post: all keys have been re-hashed and inserted into ht
	HINT - use insertMap to re-hash the keys. Everything has been completed for you except the copy/re-hash.
	Free the temp data as you copy/re-hash.
*/
void _reSizeTable(struct hashMap *ht, int newCap) {
	struct hashLink *cur, *del; /* Used to free the old hash links and iterate through them */
    struct hashLink **temp = ht->table; /* pointer to the old table */
    int tempSize = ht->tableSize; /* size of the old table */
    _initMap(ht, newCap, ht->hashID); /* Re-initialize the table */
    int i;
    ValueType tempVal;
    KeyType tempKey;
    struct hashLink *tempHash;
    /* FIX ME */
    for(i =0; i< tempSize; i++){
        if(temp[i]!=NULL){
            tempVal = temp[i]->value;
            tempKey = temp[i]->key;

            insertMap(ht, tempKey, tempVal);

            tempHash = temp[i]->next;

            while(tempHash!= NULL){
                tempVal = tempHash ->value;
                tempKey = tempHash->key;
                insertMap(ht, tempKey, tempVal);

                tempHash=tempHash->next;
            }

        }
        else{
            ;//do nothing
        }
    }
    free(temp);
    free(tempHash);
    free(cur);
    free(del);

    return;
}

/*
	insertMap: insert the key/value into a hash link - no duplicate keys are permitted
	param1: ht - the map
    param2: k - the key to insert - in this case, the word
	param3: v - the value to insert - in this case, the number of occurrences
	pre: ht is not empty
	post: map contains the key/value
	post: count has been incremented

    Duplicate values - if a duplicate key is found, leave it and insert the new value in the link
    Ex. You can't have two hash links for the word 'bobcat', but you can have many links in the same bucket
    Concordance will mange the word count (value) - the hash is not concerned with counts

    You must monitor the load factor and resize (double size) when the load factor is greater than LOAD_FACTOR_THRESHOLD (.75)
    Use the load factor function - contains an explanation of load factor
*/
void insertMap(struct hashMap *ht, KeyType k, ValueType v) {
    /* hash the key */
	int hash, newCap, counter, bucketHolder, sizeHolder;
	struct hashLink *newLink;
	struct hashLink *cur;
	struct hashLink *prev;
	double checkLoad;
	//KeyType keyHolder;
	counter =0;

	hash = _hashValue(k, ht->hashID);
	hash = hash % ht->tableSize;

	//printf("hash value %d\n", hash);

    /* FIX ME */
    /* create and initialize new link */
    newLink = malloc(sizeof(struct hashLink));
    newLink->value = v;
    newLink->key = k;
    newLink->next = NULL;

    if(ht->table[hash]==NULL){ // does not exist yet
        ht->table[hash] = newLink;
        ht->count++;
        ht->bucketCount++;

        //printf("**added key:'%s' into table[%d] level 0\n", newLink->key, hash);
    } else { // something exists at level 0
        //printf("collision happened!\n");
        if(strcmp(ht->table[hash]->key,k)==0){
            ht->table[hash]->value=v;
        } else{

            cur=ht->table[hash];
            while(cur!=NULL && strcmp(cur->key,k)!=0){
                //printf("%s\n", cur->key);
                counter++;//gone down
                prev=cur;

                cur=cur->next;

                //printf("level is %d\n", counter);
            }
            if(prev->next==NULL){
              prev->next=newLink;
              ht->count++;
              //printf("**added key:'%s' into table[%d] level %d\n", newLink->key, hash, counter);
            }

        }

    } // end of else
    /* check load factor and re-size table */
    bucketHolder = ht->bucketCount;
    sizeHolder = ht->tableSize;
    //printf("bucket count %d\n", bucketHolder);
    //printf("table size %d\n", sizeHolder);


    checkLoad = (float)bucketHolder/(float)sizeHolder;

    //printf("LOAD: %f\n", checkLoad);


    if(checkLoad > .75){
        printf("resizing table!\n");
        newCap = sizeHolder * 2;

        //printf("table size before resize %d\n", sizeHolder);
        _reSizeTable(ht, newCap);
        //printf("table size after resize %d\n", ht->tableSize);

    }


    counter=0;

    return;
}//end of insertMap

/*
	containsKey: determines whether the key is contained in the map
	param1: ht - the map
	param2: k - the key to search for
	pre: ht is not null
	post: none
	return: return 0 is not found, otherwise return 1
*/
int containsKey(struct hashMap *ht, KeyType k) {
	/* FIX ME */
	assert(ht!=NULL);

	int hash, reval;
	struct hashLink *cur = malloc(sizeof(struct hashLink));
	reval = 0;

    /* hash the key */
    hash = _hashValue(k, ht->hashID);
    hash = hash % ht->tableSize;
    cur=ht->table[hash];
    /* search table for the key - return the appropriate value */
    if(ht->table[hash]==NULL){
        reval = 0;
        return reval;
    }

    while(cur!=NULL){
        //printf("key is %s\n", cur->key);
        if(strcmp(cur->key, k) == 0){
            reval = 1;
            return reval;
        }
        cur=cur->next;
    }

	return reval;
}

/*
	removeKey: find the hash link for the key and remove it, also free the memory for the hash link
	If unable to find the key, then print an appropriate message
	param1: ht - the map
	param2: k - the key to remove
	pre: ht is not NULL
	post: key has been removed from the table
	post: count has been decremented
	HINT - If the map only contains a single hash link, it is a special case
	removing the solitary link should set the table entry to NULL
 */
void removeKey(struct hashMap *ht, KeyType k) {
	/* FIX ME */
	assert(ht!=NULL);
    int hash;
    struct hashLink *cur;
	struct hashLink *prev;
    /* check for the key, if not found, then print message and return */
    if(!containsKey(ht, k)){
        printf("key '%s' not found!\n", k);
        return;
    }

    /* hash the key */
    hash = _hashValue(k, ht->hashID);
    hash = hash % ht->tableSize;
    /* special case for single link */
    if(ht->table[hash]->next==NULL && strcmp(ht->table[hash]->key, k)==0){
        ht->table[hash] = NULL;
    }
    /* find key and remove it */

    /*if it is a top key with links*/
    if(strcmp(ht->table[hash]->key, k)==0 && ht->table[hash]->next !=NULL){
       ht->table[hash] = ht->table[hash]->next;
    }

    /*some other level other than 0*/

    cur=ht->table[hash];
    while(strcmp(cur->key, k)!= 0){
        prev=cur;
        cur= cur->next;
    }
    prev->next = prev->next->next;




}

/*
	valAtKey: return the value stored at the key
	param1: ht - the map
	param2: k - the key to search for
	pre: ht is not null
	pre: if key not found, then display an appropriate message
	post: none
	return: return the value found at the key
*/
ValueType valAtKey(struct hashMap *ht, KeyType k) {
/* FIX ME */
int hash;
struct hashLink *cur;

    /* check for the key, if not found, then print message */
    if(!containsKey(ht, k)){
        //printf("key '%s' not found!\n", k);
        return -1;
    }

    /* hash the key */
    hash = _hashValue(k, ht->hashID);
    hash = hash % ht->tableSize;

    /* search table for the key and return the current value */
    cur = ht->table[hash];
    while(strcmp(cur->key, k)!=0){
        cur=cur->next;
    }

return cur->value;
}

/*
	sizeMap: returns the number of hashLinks in the map
	param1: ht - the map
	pre: ht is not NULL
	post: none
	return: the bucketCount of the hash table
	this will be the number of 'chains' in the table
*/
int fullBuckets(struct hashMap *ht) {
	return ht->bucketCount;
}

/*
	emptyBuckets: returns the number of empty buckets in the table, these are buckets which have no hashlinks in them
	param1: ht - the hash table
	pre: ht is not null
	post: no changes to the table
	return: the number of empty buckets in the table
	HINT - you need to check the hash map for NULLs
*/
int emptyBuckets(struct hashMap *ht) {
    int counter;
	counter = (ht->tableSize)-(ht->bucketCount);

	return counter;
}

/*
	linkCount: returns the number of hashLinks in the map
	param1: ht - the map
	pre: ht is not NULL
	post: none
	return: the count of the hash table
	this will be the total number of hash links in the table
*/
int linkCount(struct hashMap *ht) {
    return ht->count;
}

/*
	printMap: prints the contents of the hash map
	param1: ht - the map
	pre: ht is not NULL
	post: map has been printed to standard output
	return: contents of the hash map are displayed via standard output - see format below
	bucket x: key (value), key (value, ....
    Ex. Bucket 1: cat (1), dog (1), the (5)...
*/
void printMap(struct hashMap *ht) {
    int i;
	int tableSize;
	struct hashLink *cur;
	tableSize = ht->tableSize;
	//printf("%d\n", tableSize);
	for(i=0; i<tableSize; i++){
        if(ht->table[i]!=NULL){
            printf("bucket %d:", i);
            cur=ht->table[i];
            while(cur!=NULL){
                printf(" %s (%d),", cur->key, cur->value);
                cur=cur->next;
            }
            printf("\n");
        }
        else{
            printf("bucket %d: empty\n", i);
        }
    }


}

/*
	tableLoad: determine the load of the table
	there are a couple ways you can calculate this - we want full buckets / empty buckets
	we are not concerned with the number of hash links - we are assuming a reasonable hash
	param1: ht - the hash table
	pre: ht is not null
	post: no changes to the table
	return: returns the ratio of: (number of hash links) / (number of buckets)
	HINT - cast one of the operands to a float, otherwise you have integer division
*/
float tableLoad(struct hashMap *ht) {
	/* FIX ME */
	int bucketHolder, sizeHolder;
	double checkLoad;



	bucketHolder = ht->bucketCount;
    sizeHolder = ht->tableSize;
    //printf("bucket count %d\n", bucketHolder);
    //printf("table size %d\n", sizeHolder);


    checkLoad = (float)bucketHolder/(float)sizeHolder;

	return checkLoad;
}

/*
	capacityMap: returns the number of buckets in the map
	param1: ht - the hash map
	pre: - ht is not null
	post: no changes to the map
	return: return the tableSize
*/
int capacityMap(struct hashMap *ht) {
    return ht->tableSize;
}

/*
	freeMap: free all memory used by the buckets
	param1: ht - the hash map
	pre: - ht is not null
	post: memory used by the hash buckets has been freed
*/
void _freeMap (struct hashMap *ht) {
	/* FIX ME */
	struct hashLink *cur;
	struct hashLink *prev;
	int i;
	for(i=0; i < ht->tableSize; i++){
        if(ht->table[i]!=NULL){
            cur =ht->table[i];
            while(cur!=NULL){
                prev=cur;
                free(prev);
                cur=cur->next;
            }
            free(cur);
        }
	}


}

/*
	freeMap: deallocate buckets and the hash map
	param1: ht - the hash map
	pre: - ht is not null
	post: memory used by the hash buckets and the hash table has been freed
*/
void deleteMap(struct hashMap *ht) {
	assert(ht != NULL);

	_freeMap(ht);/* free all memory used by the buckets */
	free(ht);/* free the hash map */
}
