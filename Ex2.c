/* CS260 - Assignment 2 - EX 2*/
/* Name:Joe Aguilera
 * Date:10/11/2015
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>


void sort(int *numbers, int n){
     /*Sort the array according to value in ascending order*//*int swaps=0;*/

	int i,j;
	int temp;

    for(i=0;i<n-1;i++){
        for(j=0;j<n-1-i;j++){
            if(numbers[j]>numbers[j+1]){
                temp = numbers[j+1];
                numbers[j+1]=numbers[j];
                numbers[j]=temp;
                /*swaps++;*//* counter for comparing answers with sort analyst*/
            }
        }
   }
  /* printf("comparisons %i\n", counter);*/

	return;

}

void generate(int *numbers, int n) {
    /*Generate random numbers to store into students */
    int i;
    int counter;
    srand(time(NULL));

    for(i=0; i<n; i++){
        counter = rand()%100;
        /* printf("counter value %i\n", counter);*/
        numbers[i] = counter;
        /* printf("Person: %i", i+1);*/
    }



    return;
}

void display(int *numbers, int n){
    int i;
    for(i=0; i<n;i++){
        printf("The the first value of spot: %i", i);
        printf(", is %i\n", numbers[i]);
    }
    printf("\n");

}


int main(){
    int *students=NULL;
    /*Declare an integer n and assign it the value 20.*/
    int n=20;

    /*Allocate memory for n students using malloc.*/

    students = malloc(sizeof(int)*n);

    /*Generate random integers for the array, using rand().*/
    generate(students, n);

    /*Print the contents of the array.*/

    display(students, n);

    /*Pass this array along with n to the sort() function*/

    sort(students, n);

    /*Print the contents of the sorted array.*/

    display(students, n);

    return 0;
}
