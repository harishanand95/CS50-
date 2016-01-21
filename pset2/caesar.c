#include<cs50.h>
#include<stdlib.h>   // for atoi()
#include<ctype.h>   //for toupper() isalpha()
#include<stdio.h>
#include<string.h>
int main(int argc,char* argv[])
{
	if(argc == 2)  
	{
		string k = GetString();
		int j , key = atoi(argv[1]);
		int n = strlen(k);
		char A[26];
		for(int i = 0;i<26;i++)
		{
			A[i]=(char)97+i;      //storing characters in an array
		}
		for(int i=0;i<n;i++)
		{      
			if(isalpha(k[i]))
			{   if(isupper(k[i])) //checking with a uppercase letter
				{   for(j=0;j<26;j++)
					{     if(k[i]==toupper(A[j]))
						{  
							k[i]= toupper(A[(j+key)%26]); //storing uppercase letters in the data array
							break;
						}
					} 
				}       
				else
				{
					for(j=0;j<26;j++)
					{
						if(k[i]==A[j])
						{  
							k[i] = A[(j+key)%26]; //storing in the input array lowercase letters
							break;
						}
					} 
				}     
			}
			else
				continue;//any other charcter other than a letter, leave it
		}           
		for(int i=0;i<n;i++)
		{
			printf("%c",k[i]); //printing of the (now) altered input array
		}
		printf("\n");
		return 0;  
	}
	else
		printf("Error!"); //error in case of wrong command line arguments
	return 1;
}
