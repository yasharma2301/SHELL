/* Name:ID: Yash Sharma
Teammatename(s): Tumul Vyas
*/
#include <stdio.h> 
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX_LINE 80 /* The maximum length command */
char history[10][MAX_LINE];
int no_of_args;
int main(void){
	char *args[MAX_LINE/2 + 1]; /* command line arguments */
	int should_run = 1; /* flag to determine when to exit program*/
	no_of_args =0;	
	while (should_run)
	{
		int i=0;
		char s[MAX_LINE];
		char *arg;
		printf("osh>"); 
		fflush(stdout);
		scanf("%[^\n]",s);
		getchar();
		bool j;
		if(strcmp(s,"history")==0)
		{
			if(no_of_args==0)
			{
			printf("No argument is entered till now\n");
				continue;
			}
			for(int j=0;j<no_of_args;j++)
			{
				printf("%d %s\n",j+1,history[j]);
			}
			continue;
		}
		if(s[0]=='!')
		{
			if(no_of_args == 0)
			{
			printf("Sorry, No arguments till now\n");
			continue;
			}
			if(s[1]=='!')
			{
				update(history[0]);
				char s1[MAX_LINE];
				strcpy(s1,history[0]);
				break_into_args(s1,args,&j);
			}
			else
			{
				int x= s[1]-48;
				if(x>=11&&x<=0)
				{
				printf("Not an Allowed operation\n");
					continue;
				}
				update(history[x]);
				char s1[MAX_LINE];
				strcpy(s1,history[x]);
				break_into_args(s1,args,&j);
			}
		}
		else
		{	
			update(s);
			break_into_args(s,args,&j);
		}
		pid_t child_pid;
		child_pid = fork();
		if(strcmp(*(args),"quit")==0)
			exit(0);
		if(child_pid==0)
		{
			execvp(args[0], args);
			fprintf (stderr,"an error occured in execvp\n");
			abort();
		}
		if(j==true&&child_pid!=0)
			wait();
	}
}
void update(char *s)
{
	for (int i = 9; i>0; i--)
    	strcpy(history[i], history[i-1]);
        strcpy(history[0],s);
        no_of_args++;
    	if(no_of_args>10)
	{
    		no_of_args=10;
    	}
}
void break_into_args(char *s, char **args,bool *j)
{
	int i=0;
	char *ptr[41] ;
	ptr[0]= strtok(s," ");
	while(ptr[i]!=NULL)
	{
		*(args+i)=ptr[i];
		ptr[++i] = strtok(NULL," ");
	}
	char ptr1[10];
	strcpy(ptr1,*(args+i-1));
	ptr[i] = strtok(*(args+i-1),"&");
	if(strcmp(ptr[i],ptr1)==0)
	{
		*(args+i)=NULL;
		*j = true;
	}
	else
	{
		*(args+i-1)=ptr[i];
		*(args+i)=NULL;
		*j= false;
	}
}
