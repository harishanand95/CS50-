#include<stdio.h>
#include<cs50.h>
int main()
{
    int height;
    string s="########################"; //24 #'s stored for display
        do
        {
             printf("Height:");
             height=GetInt();
        }while(!( (height>=0) && (height<=23) )); //loop for asking proper height 
    
        for(int i = 2;i<=height+1;i++)
        {
            printf("%*.*s\n",height+1,i,s); //* here acts as both variable width and precision
        }
    return 0;
}
