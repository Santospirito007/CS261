/* CS260 - Assignment 2 - EX 3*/
/* Name: Joe Aguilera
 * Date:10/11/2015
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct person {
	int age;
	char sex;
};

void sort(struct person* people, int n) {
	/*Sort the given array of people by age, of length n*/
	/*int swaps=0;*/

	int i,j;
	struct person temp;

    for(i=0;i<n-1;i++){
        for(j=0;j<n-1-i;j++){
            if(people[j].age>people[j+1].age){
                temp = people[j+1];
                people[j+1]=people[j];
                people[j]=temp;
                /*swaps++;*//* counter for comparing answers with sort analyst*/
            }
        }
   }
  /* printf("comparisons %i\n", counter);*/

	return;
}

/*This function can be identical to the previous sort function, however it needs to return the total number of comparisons carried out in the sort.
If you want to attempt to optimize the sort, then you are welcome to do so */

int sortAnalysis(struct person* people, int n) {
     /*Sort the given array of persons of length n
	 Return the number of comparisons required to terminate the algorithm */
    int swaps=0;
    int i,j;
    struct person temp;

    for(i=0;i<n-1;i++){
        for(j=0;j<n-1-i;j++){
            if(people[j].age>people[j+1].age){
                temp = people[j+1];
                people[j+1]=people[j];
                people[j]=temp;
                swaps++;/*counts how many swaps occur in the sort*/
            }

        }
   }

	 return swaps;
}

void display(struct person* people, int n) {

    int i;

    for(i = 0; i<n; i++){
        printf("Person: %i", i+1);
        printf(" Age: %i", people[i].age);
        printf(", Sex: %c\n", people[i].sex);


    }

    /*seperator for code */

    printf("\n\n");
    return;
}

void generate(struct person* people, int n) {
    /*Generate random age and sex for 10 persons and store in people
    Age is between 18 and 90 - sex is either M or F
    Calculate random numbers between using rand().
    Simply assigning ages 19, 20, 21.. is not sufficient*/
    int counter;
    int i;
    int j;
    int sex_random;
    srand(time(NULL));

    for(i=0; i<n; i++){
        counter = rand()%(90-18+1)+18;
        /* printf("counter value %i\n", counter);*/
        people[i].age = counter;
        /* printf("Person: %i", i+1);
        printf(" age is: %i\n", people[i].age);*/
    }

    for(j=0; j< n; j++){
        sex_random = rand()%2+1;
        /* printf("sex_random value %i\n", sex_random);*/
        if(sex_random == 2){
            people[j].sex='F';

        }
        else{
            people[j].sex='M';
        }
      /*  printf("Person: %i", j+1);
        printf(" sex is: %c\n", people[j].sex);*/
    }


    return;
}


int main(){
    int counter;
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    struct person *people=NULL;


    /*Allocate memory for an array of n persons using malloc.*/


    people = malloc(sizeof(struct person)*n);


    /*Fill this array with random persons with ages between 18 and 90 and random genders, using rand().*/
    /*call generate*/
    generate(people, n);

	/*Pass this array along with n to the display() function.*/
	display(people, n);

    /*Pass this array along with n to the sort() function.*/
    sort(people, n);

    /*Pass this array along with n to the display() function.*/
    display(people, n);

	/*Pass this array along with n to the sortAnalysis() function.*/
	counter=sortAnalysis(people, n);

	/*Display the number of comparisons the function returns.	Did it matter that the array was already sorted? Why? - Display your answer in comments bellow
	Note - this will depend on your implementation. There is not one answer*/
	printf("This is how many comparisons the program did: %i", counter);

	/*
        Yes it did matter, since it was already sorted, it never did a comparison calculation. It looked at values and
        never did anything
	*/

    return 0;
}

