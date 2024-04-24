#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include "eventbuf.h"

struct eventbuf *eb;

int flag;
int num_prod;
  int num_cons;
  int num_events;
  int num_unconsumed_events;


sem_t *mutex;
sem_t *items;
sem_t *spaces;

sem_t *sem_open_temp(const char *name, int value)
{
    sem_t *sem;

    // Create the semaphore
    if ((sem = sem_open(name, O_CREAT, 0600, value)) == SEM_FAILED)
        return SEM_FAILED;

    // Unlink it so it will go away after this process exits
    if (sem_unlink(name) == -1) {
        sem_close(sem);
        return SEM_FAILED;
    }

    return sem;
}

void *producer(void *arg)
{
  (void)arg;
  int producer_id = *(int *)arg;

  for (int event_num = 0; event_num < num_events; event_num++)
  {
    sem_wait(spaces);
    sem_wait(mutex);

    eventbuf_add(eb, producer_id * 100 + event_num);

    sem_post(mutex);
    sem_post(items);

    printf("P%d: adding event %d\n", producer_id, producer_id * 100 + event_num);

  }

  printf("P%d: exiting\n", producer_id);

  return NULL;
  
}

void *consumer(void *arg)
{
  (void)arg;
  int id = *(int *)arg;

  while(!flag)
  {
    sem_wait(items);

    sem_wait(mutex);

    if(eventbuf_empty(eb)){
      sem_post(mutex);
      break;
    }

    int event = eventbuf_get(eb);

    sem_post(mutex);

    sem_post(spaces);

    printf("C%d: got event %d\n", id, event);
  }

  printf("C%d: exiting\n",id);

  return NULL;
  
}

int main(int argc, char *argv[])
{
  if (argc != 5) {
    printf("Usage: %s num_prod num_cons num_events num_unconsumed_events\n", argv[0]);
    printf("%d",argc);
    return 1;
  }

  else
  {
  num_prod = atoi(argv[1]);
  num_cons = atoi(argv[2]);
  num_events = atoi(argv[3]);
  num_unconsumed_events = atoi(argv[4]);
  }

   mutex = sem_open_temp("pc-project-semaphore", 1);
   items = sem_open_temp("pc-items-semaphore",0);
   spaces = sem_open_temp("pc-spaces-semaphore", num_unconsumed_events);

    eb = eventbuf_create();

  pthread_t producers[num_prod];
  pthread_t consumers[num_cons];

  for (int i = 0; i < num_prod; i++)
  {
    int *prod_id_count = malloc(sizeof(int));
    *prod_id_count = i;
    pthread_create(&producers[i], NULL, producer, prod_id_count);
  }

  for (int i = 0; i < num_cons; i++)
  {
    int *cons_id_count = malloc(sizeof(int));
    *cons_id_count = i;
    pthread_create(&consumers[i], NULL, consumer, cons_id_count);
  }

  for (int i = 0; i< num_prod; i++){
    pthread_join(producers[i], NULL);
  }  

  

  for (int i = 0; i < num_cons; i++)
  {
    sem_post(items);
  }

  flag = 1;

  for (int i = 0; i < num_cons; i++)
  {
    pthread_join(consumers[i], NULL);
  }

  eventbuf_free(eb);

  sem_close(mutex);
  sem_close(spaces);
  sem_close(items);
  
  
  sem_unlink("pc-item_semaphore");
  sem_unlink("pc-mutex-semaphore");
  sem_unlink("pc-spaces-semaphore");
}

