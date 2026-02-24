#include <stdio.h>
#include <stdlib.h>

int main(){//int argc, char ** argv){
        
        int rightnub = rand() % 10;

        int userinput = 0;

        printf("find the right number between 0 and 10");

        do{
                printf("Enter number:");
                scanf("%d", &userinput);
                userinput %= 10;
                printf("You have chosen : " + string(userinput) + '\n');

                if      (userinput < rightnub) printf("the right number is bigger");
                else if (userinput > rightnub) printf("the right number is smaller");

        }while (userinput!=rightnub);

        printf("You found the right number!");

        return 0;
}