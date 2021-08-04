//Enter your name here: Yaqian Yang
//Enter your email here: yang.yaqi@northeastern.edu
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t chopstick[5];//lock variable

// Thread to be executed
void *philosopher(void *x)
{
 //Treat variable x as a pointer to an int and then extract the value into n
    int* a=(int*)x;
    int n=*a;
    /*-----Insert your code here----*/
    int right = n;
    int left = n - 1;
    if(left == -1) left = 4;
    printf("philosopher %d is thinking \n", n + 1);
    pthread_mutex_lock(&chopstick[left]);
    pthread_mutex_lock(&chopstick[right]);
    printf("philosopher %d is eating with [%d] [%d] \n", n + 1, left, right);
    sleep(1);
    pthread_mutex_unlock(&chopstick[left]);
    pthread_mutex_unlock(&chopstick[right]);
    printf("philosopher %d finishes eating \n", n + 1);
}


/*------------ Main Program---------*/
int main()
{
    pthread_t threads[5];
    int i,val[5];
    
//initializing the mutex
    for(i = 0; i < 5; i++){
        pthread_mutex_init( &chopstick[i], NULL);
    }
//create and run the thread
    for(i = 0; i < 5; i++){
        pthread_create( &threads[i], NULL, philosopher, (void*)&i);
    }
//wait until all the threads are done
    for(i=0; i<5; i++)
        pthread_join(threads[i],NULL);
// Destroying the mutex
    for(i=0; i<5; i++)
        pthread_mutex_destroy(&chopstick[i]);
    return 0;
}
