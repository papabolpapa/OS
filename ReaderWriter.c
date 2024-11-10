
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
sem_t r, w;          // Semaphores for reader and writer
int rcount = 0;      // Reader count
void* reader(void* arg) {
    sem_wait(&r);    // Wait on reader semaphore
    rcount++;        // Increment reader count
    if (rcount == 1) {
        sem_wait(&w); // If first reader, lock writer
    }
    sem_post(&r);
    printf("Reading Operation Is Performed\n");
    sleep(1); 
    sem_wait(&r);    // Wait on reader semaphore
    rcount--;        // Decrement reader count
    if (rcount == 0) {
        sem_post(&w); 
    }
    sem_post(&r);    
    return NULL;
}
void* writer(void* arg) {
    sem_wait(&w);
    printf("Writing Operation Is Performed\n");
    sleep(1); 
    sem_post(&w);
    return NULL;
}
int main() {
    pthread_t readers[5], writers[5];
    sem_init(&r, 0, 1);
    sem_init(&w, 0, 1);
    for (int i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
        pthread_create(&writers[i], NULL, writer, NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }
    sem_destroy(&r);
    sem_destroy(&w);
    return 0;
}
