
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    // position of the the last digit
  int position;
  
    // character array to hold user input
  char *num;
    // character array to hold single digits
  char *SingleDigits[] ={"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    // character array to hold number above 10 and below 20.
  char *DoubleDigits[] = {"", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    // character array to hold two digits numbers with the second digit being zero.
  char *TyNum[] = {"", "", "twenty", "thrity", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    // Character array to hold the tenth place of the user input.
  char *TenPlace[] = {"","", "hundred", "thousand","", "", "million", "", "", "billion" };
  printf ("Enter a number: "); 
  scanf ("%[^\n]", &num);// scanning the character array including the white spaces.  
  position = strlen(num); // gives the length of the number. 

  // Handling single digits
  if (position == 1) 
    printf("%s\n", SingleDigits[*num]);

  // two cases for two digits numbers
 else if (position == 2) 
   {
     // 11 - 19 
     if (*num == '1')
       printf ("%s\n",DoubleDigits[*(num+1)] );
     // Two digit numbers with the second digit zero
     else if (*num != '0' && *(num+1) == 0)
       printf ("%s\n",TyNum[*num] );
     //The rest of the two digits numbers
     else
       {
       prinf("%s ", TyNum[*num]);
     printf("%s\n", SingleDigits[*(num+1)]);
       } 
   }

  // for numbers with three digits or more.
 else if (position >= 3) 
   {
     printf("%s ", SingleDigits[*num]);
     printf("%s ", TenPlace[*(num+1)]);
     printf("%s ", TyNum[*(num+2)]);
     printf ("%s\n", SingleDigits[*(num + 3)]);
   }
}
