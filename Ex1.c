/* CS260 - Assignment 2 - EX 1*/
/* Name:Joe Aguilera
 * Date:10/10/2015
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
	Desc: converts ch to upper case
	Precondition: ch is a lower case char (a-z).
	Postcondition: ch is return as upper case.
*/
char toUpperCase(char ch){
    ch=ch-32;


    return ch;
}

/*
	Desc: converts ch to lower case
	Precondition: ch is a upper case char (a-z).
	Postcondition: ch is return as lower case.
*/
char toLowerCase(char ch){
    ch=ch+32;

    return ch;

}

void studly(char* ch){
    int i;
    int j;
     /*Convert to studly caps
	 It is safe to assume that the string is terminated by '\0'*/

   /*printf("The string before change is->%s",ch);*/

    for(i=0;i<=strlen(ch);i++){
        if(ch[i]>=97&&ch[i]<=122){
            ch[i]=toUpperCase(ch[i]);
        }
    }

    for(j=1;j<=strlen(ch);j+=2){
        if(ch[j]>=65&&ch[j]<=90){
            ch[j]=toLowerCase(ch[j]);
        }
    }

   /* printf("\nThe string in after the change is->%s",ch);*/


    return;

}

int main(){
    char str[100];
    int i;



    /*Read word from the keyboard using scanf
	Max length 100 characters including string terminator*/


    printf("Enter any string without spaces-> of 100 characters or less: \n");
    scanf("%s",str);
   /*  printf("%s", str); */


    /*Call studly*/
    studly(str);

    /*Print the new word*/

    printf("The string after the change is-> %s ",str);
    /*
    for(i=0; i<=strlen(readIn); i++){
        printf("%c", readIn[i]);
    }*/


    return 0;
}
