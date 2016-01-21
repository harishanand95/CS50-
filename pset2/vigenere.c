#include<cs50.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
int main(int argc,char* argv[])
{
	int flag=-1;
	if(argc == 2)
	{
		flag=0;
		for(int i = 0; argv[1][i] != '\0'; i++)
		{   
			if(!(isalpha(argv[1][i])))
			{
				flag++;      // a condition to check if all elements is indeed a char
				break;
			}  
		}   
	}

	if(flag == 0)
	{
		string p = GetString(); //input stored in p
		int r=0;
		int  j,l=0;
		int n = strlen(p);
		int m = strlen(argv[1]);
		char k[26];
		for(int i=0;i<26;i++)
		{
			k[i] = (char) 97 + i;     //storing of all alphabets 
		}

		for(int i=0;i<n;i++)
		{      
			if(isalpha(p[i])) //checking for alpha in input
			{  
				if(isupper(p[i])) //for upper case letter in input 
				{   for(j=0;j<26;j++)
					{     if(p[i]==toupper(k[j]))
						{  l=0;
							while(tolower(argv[1][r])!=k[l])
							{
								l++; //to find the value of its subsequent key character
							}

							p[i]= toupper(k[(l+j)%26]); //encrypted uppercase
							if( r == ( m - 1 ) ) //m-1 due to ++r usage(not r++)
							{ 
								r=0;
							} //r keeps the count of keywords,and creates a cycle 
							else
								++r;
							break;
						}
					} 
				}
				else
				{
					for(j=0;j<26;j++)
					{ 
						if(p[i]==k[j])
						{  l=0;
							while(tolower(argv[1][r])!=k[l])
							{
								l++;//to find the value of its simultaneous key character
							}
							p[i] = k[(l+j)%26];//encryption
							if( r==(m-1) )//m-1 due to ++r
							{
								r = 0; //r goes to back to 0, thus a cycle of keyword is obtained  
							}
							else
								++r;
							break;
						} 
					} 
				} 
			}          
			else
				continue;
		}           
		for(int i=0;i < n;i++)
		{
			printf("%c",p[i]);
		}
		printf("\n");
		return 0;  
	}
	else
		printf("Error!");
	return 1;
}   
