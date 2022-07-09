#include <stdio.h>
#include <stdlib.h>
  
int main()
{

   FILE *f1;
   char final[100],out[100];

   int num,i;
   printf("Enter total number of files:");
   scanf("%d",&num);
   printf("Enter output file name:");
   scanf(" %s",&out);
   FILE *f3 = fopen(out, "w");
   char c;
   for(i=1;i<=num;i++)
   {
       printf("Enter input file name:");
       scanf(" %s",final);
       f1 = fopen(final,"r");
       f3 = fopen(out, "a");
       if(f1==NULL || f3==NULL)
       {
            puts("Could not open files");
            exit(0);
       }
       else
       {
             while ((c = fgetc(f1)) != EOF)
                fputc(c, f3);
       }
       fclose(f1);

   fclose(f3);
   
   }
   printf("\nContent copied to %s",out);

   return 0;
}
