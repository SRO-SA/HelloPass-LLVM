#include<stdio.h>
 
int main() {
   int a, b, sum;

   printf("\nEnter two numbers: ");
   scanf("%d %d", &a, &b);
  if (a < b){
printf("1st number is less than the 2nd number.");
}
if (a > b){
printf("1st number is greater than the 2nd number.");
}
    
   return(0);
}
