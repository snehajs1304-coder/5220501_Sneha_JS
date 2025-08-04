// print the days of the week

#include <stdio.h>

int main()
{
    int days;
    
    while(1)
    {
    printf("Enter the days of the week: 1-7\n");
    scanf("%d",&days);

    switch(days)
    {
        case 1: printf("SUNDAY");
           return 0;
        case 2: printf("MONDAY");
           return 0;
        case 3: printf("TUESDAY");
           return 0;
        case 4: printf("WEDNESDAY");
           return 0;
        case 5: printf("THURSDAY");
           return 0;
        case 6: printf("FRIDAY");
           return 0;
        case 7: printf("SATURDAY");
           return 0;
        default:
          printf("Invalid please Enter a valid input for days: 1-7\n");
        
    }
    }

    return 0;
    
}