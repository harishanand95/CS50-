#include<stdio.h>
#include<math.h>
#include<cs50.h>
int main()
{    
     int foo(int);
     int coins,amt;
     float amount;
     printf("O hai!  ");
     do
     { 
           printf("Howmuch change is owed?\n");
           amount = GetFloat();
     }while( amount < 0);
     
     amount*=100;
     amt = round(amount);
     coins = foo(amt);
     printf("%d\n",coins);
     return 0;
}     
int foo(int amt)
{
   int total = 0;
   while((amt)>=25)
   {
        total++;
        amt = amt-25;
   }     
   while((amt)>=10)
   {
        total++;
        amt = amt-10;
   }     
   while((amt)>=5)
   {
        total++;
        amt = amt-5;
   }     
   while((amt)>=1)
   {
        total++;
        amt = amt-1;
   }     
   return total;
 }  
   
