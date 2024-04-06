// Daniel Lounsbury
// CS444

#include <pthread.h>
#include <stdio.h>

#define THREADCOUNT 2
#define COUNTERUPPERBOUND 25

void *counter(void *arg)
{

int *threadnum = (int *)arg;

for (int i = 0; i < COUNTERUPPERBOUND+1; i++)
{
  printf("thread %d : %d\n",*threadnum+1,i); 
}
 return NULL;
}

void init_threads(pthread_t threads[], int thread_args[])
{
  puts("Launching threads");

for (int i = 0; i < THREADCOUNT; i++)
{
  thread_args[i] = i;
  pthread_create(&threads[i], NULL, counter, (void*)&thread_args[i]);
}
}

void join_threads(pthread_t threads[])
{
for (int i = 0; i < THREADCOUNT; i++)
{
pthread_join(threads[i], NULL);
}
puts("Threads complete!");
}

int main()
{
pthread_t threads[THREADCOUNT];
int thread_args[THREADCOUNT];
init_threads(threads, thread_args);
join_threads(threads);
}









// // Daniel Lounsbury
// // CS444

// #include <pthread.h>
// #include <stdio.h>

// #define THREADCOUNT 2

// void *counter(void *arg)
// {

// int *threadnum = (int *)arg;

// for (int i = 0; i < 5; i++)
// {
//   printf("thread %d : %d\n",*threadnum,i); 
// }
//  return NULL;
// }

// int main()
// {
// pthread_t threads[THREADCOUNT];
// int thread_args[THREADCOUNT];

// puts("Launching threads");

// for (int i = 0; i < THREADCOUNT; i++)
// {
//   thread_args[i] = i;
//   pthread_create(&threads[i], NULL, counter, (void*)&thread_args[i]);
// }

// for (int i = 0; i < THREADCOUNT; i++)
// {
// pthread_join(threads[i], NULL);
// }
// puts("Threads complete!");
// }


