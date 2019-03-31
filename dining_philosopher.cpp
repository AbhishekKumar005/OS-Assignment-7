#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
  
#define N 5 
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 
#define LEFT (pid + 4) % N       // pid = philosopher id or number
#define RIGHT (pid + 1) % N 
  
int state[N]; 
int ph[N] = { 0, 1, 2, 3, 4 }; 
  
sem_t mutex;    // Mutex will ensure no two philosophers may access the pickup or putdown at the same time.
sem_t S[N];     //  to control the behavior of each philosopher
  
void test(int pid) 
{ 
    if (state[pid] == HUNGRY 
        && state[LEFT] != EATING 
        && state[RIGHT] != EATING) { 
        // state that eating 
        state[pid] = EATING; 
  
        sleep(2); 
  
        printf("Philosopher %d takes fork %d and %d\n", 
                      pid + 1, LEFT + 1, pid + 1); 
  
        printf("Philosopher %d is Eating\n", pid + 1); 
  
        sem_post(&S[pid]);                                  } 
} 
  
// take up chopsticks 
void take_fork(int pid) 
{ 
  
    sem_wait(&mutex); 
  
    // state that hungry 
    state[pid] = HUNGRY; 
  
    printf("Philosopher %d is Hungry\n", pid + 1); 
  
    // eat if neighbours are not eating 
    test(pid); 
  
    sem_post(&mutex); 
  
    // if unable to eat wait to be signalled 
    sem_wait(&S[pid]); 
  
    sleep(1); 
} 
  
// put down chopsticks 
void put_fork(int pid) 
{ 
  
    sem_wait(&mutex); 
  
    // state that thinking 
    state[pid] = THINKING; 
  
    printf("Philosopher %d is putting fork %d and %d down\n", 
           pid + 1, LEFT + 1, pid + 1); 
    printf("Philosopher %d is thinking\n", pid + 1); 
  
    test(LEFT); 
    test(RIGHT); 
  
    sem_post(&mutex); 
} 
  
void* philospher(void* num) 
{ 
  
    while (1) { 
  
        int* i = num; 
  
        sleep(1); 
  
        take_fork(*i); 
  
        sleep(0); 
  
        put_fork(*i); 
    } 
} 
  
int main() 
{ 
  
    int i; 
    pthread_t thread_id[N]; 
  
    // initialize the semaphores 
    sem_init(&mutex, 0, 1); 
  
    for (i = 0; i < N; i++) 
  
        sem_init(&S[i], 0, 0); 
  
    for (i = 0; i < N; i++) { 
  
        // create philosopher processes 
        pthread_create(&thread_id[i], NULL, 
                       philospher, &ph[i]); 
  
        printf("Philosopher %d is thinking\n", i + 1); 
    } 
  
    for (i = 0; i < N; i++) 
  
        pthread_join(thread_id[i], NULL); 
} 
