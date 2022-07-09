#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define s    10
#define NUMBER_OF_THREADS   3

void *sorter(void *params); 
void *merger(void *params);

int arr[s] = {5,3,7,1,2,9,22,6,11,8};

int res[s];

typedef struct
{
int from_index; 
int to_index;
int mid;
} parameters;


int main (int argc, const char * argv[]) 
{
   
    pthread_t tid[NUMBER_OF_THREADS];
    
    parameters *para = (parameters *) malloc(sizeof(parameters));
    para->from_index = 0;
    para->mid  = 0 +((s/2)-1)/2;
    para->to_index = (s/2) - 1;
    for(int i = 0;i<NUMBER_OF_THREADS-1;i++)
        pthread_create(&tid[0], 0, sorter, para);
    
    para = (parameters *) malloc(sizeof(parameters));
    para->from_index = s/2;
    para->mid  = s/2 + ((s/2)-1)/2;;
    para->to_index = s - 1;
    for(int i = 0;i<NUMBER_OF_THREADS-1;i++)
        pthread_create(&tid[1], 0, sorter, para);
        
    for(int i = 0;i<NUMBER_OF_THREADS-1;i++)
        pthread_join(tid[i],NULL);
    
    para = (parameters *) malloc(sizeof(parameters));
    para->from_index = 0;
    para->mid  = 0 + (s - 1)/2;
    para->to_index = s;
    pthread_create(&tid[2],0,merger,para);
    for(int i = 0;i<NUMBER_OF_THREADS;i++)
        pthread_join(tid[i],NULL);

    return 0;
}

void *sorter(void *params){

    parameters* pa = (parameters *) params;
    int start = pa->from_index,
    end = pa->to_index + 1,
    mid = pa->mid;
  
    
   for(int i =start;i<end - 1;i++)
   {
       if(arr[i]>arr[i+1])
       {
           int temp = arr[i];
           arr[i] = arr[i+1];
           arr[i + 1] = temp;
           
        i = -1;
       }
   }
    

    
    for(int i = start; i < end;i++)
    {
        res[i] = arr[i];
        
    }
    
    
    
}

void *merger(void *params){

    parameters* pa = (parameters *) params;
    int start = pa->from_index,
    end = pa->to_index + 1;
   
   for(int i =start;i< end - 1;i++)
   {
       if(res[i]>res[i+1])
       {
           int temp = res[i];
           res[i] = res[i+1];
           res[i + 1] = temp;
           
        i = -1;
       }
   }

   printf("sorted and merged array is:");
    for(int i =start; i < end ;i++)
    {
        printf("%d,",res[i]);
    }



}
 