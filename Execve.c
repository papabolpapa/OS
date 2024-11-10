//Parent.c

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void SortArray(int arr[],int n)
{
  int temp;
  for(int i=0;i<n-1;i++)
  {
    for(int j=i+1;j<n;j++)
    {
      if(arr[i] > arr[j])
      {
      temp=arr[i];
      arr[i]=arr[j];
      arr[j]=temp;
      }
    }
  }
}
int main()
{
  int arr[50],n;
  
  printf("Enter number of elements:");
  scanf("%d",&n);
  
  printf("Enter %d elements:\n",n);
  for(int i=0;i<n;i++)
  {
    scanf("%d",&arr[i]);
    }
    SortArray(arr,n);
    
    char *args[n+2];
    args[0]="./child";
    for(int i=0;i<n;i++)
    {
     asprintf(&args[i+1],"%d",arr[i]);
     }
     args[n+1]=NULL;
     
     pid_t pid=fork();
     if(pid<0)
     {
        perror("Fork");
        return 1;
      }
      if(pid==0)
      {
        execve(args [0],args,NULL);
        perror("execve");
        exit(1);
       }
       else
       {
         wait(NULL);
       }
       for(int i=1;i<=n;i++)
       {
         free(args[i]);
       }
       return 0;
 } 


//child.c
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
   int n=argc-1;
   int arr[n];
   for(int i=0;i<n;i++)
   {
     arr[i]=atoi(argv[i+1]);
     }
   printf("Reversed array:\t");
   for(int i=n-1;i>=0;i--)
   {
     printf("%d",arr[i]);
     if (i > 0) {
            printf(" ");
     }
     }
     printf("  \n");
     return 0;
}