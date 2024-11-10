#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
sem_t e,f,s;
int buff[5];
int in=0,out=0;
void* producer(void* arg){
   sem_wait(&e);
   sem_wait(&s);
   int data=rand();
   buff[in]=data;
   printf("\nProduct %d entered by %lu successfully \n",data,pthread_self());
   in = (in+1)%5;
   sem_post(&s);
   sem_post(&f);
   sleep(5);
   return NULL;
}
void* consumer(void* arg){
  int conti=0;
  int data;
  do{
     sem_wait(&f);
     sem_wait(&s);
     int data=buff[out];
     printf("\nProduct %d consumed by %lu successfully \n",data,pthread_self());
     out = (out+1)%5;
     sem_post(&s);
     sem_post(&e);
  }while(conti!=5);
  return NULL;
  
} 
void main(){
pthread_t tid[5], ctid;
sem_init(&f,0,0);
sem_init(&e,0,5);
sem_init(&s,0,1);
for(int i=0;i<5;i++){
   pthread_create(&tid[i],NULL,producer,NULL);
 }
pthread_create(&ctid,NULL,consumer,NULL);
for(int i=0;i<5;i++){
   pthread_join(tid[i],NULL);
}
pthread_join(ctid,NULL);
}   