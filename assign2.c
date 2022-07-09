#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


int main()
{

   int pipe1[2],pipe2[2],pid;
   char input[100];
   
   pipe(pipe1);
   pipe(pipe2); 
    
    printf("Enter your input messsage:");
    scanf("%[^\n]",&input);
    
    pid = fork();
    
    if(pid<0)
    {
    	printf("fork failed");
    	return 1;
    }
 
 //child process
    if (pid == 0)
    {
    	close(pipe1[1]);
    	
    	char mod[100];
    	//reading the input from parent process
    	read(pipe1[0], mod, 100);
 
 	//closing both pipes which are reading 
        close(pipe1[0]);
        close(pipe2[0]);
        
        //for loop to convert capital char to lower and lower to upper
 	for(int i=0;i<strlen(input);i++)
	{
  		if(input[i]>=65 && input[i]<=90)
			{
			     mod[i]=input[i]+32;

			}
		else if(input[i]>=97 && input[i]<=122)
			{
		             mod[i]=input[i]-32;

			}
			
	}
       
       //writing the converted message to parent back
  	write(pipe2[1], mod, strlen(mod));
        close(pipe2[1]);
 
        exit(0);
    }
    
    //parent process
    else
    {
    	char mod[100];
    	//close reading process 
    	close(pipe1[0]);
    	
    	//writing the user input 
    	write(pipe1[1],input,strlen(input));
    	close(pipe1[1]);
    
    	
    	close(pipe2[1]);
    	
    	//reading the converted message from child
    	read(pipe2[0], mod, 100);
    	//printing the converted message
        printf("Modified Message is: %s\n", mod);
        close(pipe2[0]);
    }
}
  
 
