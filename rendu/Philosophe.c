#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> // PRINTF
#include "Philosophe.h"

static void	eat(philo *tmp)
{
  tmp->state = EAT;
  tmp->stock = tmp->stock - 1;
  printf("\x1b[32mPhilosophe %d : Je mange ta mère\x1b[0m\n", tmp->id);
  sleep(2);
  tmp->state = REST;
  if (pthread_mutex_unlock(&tmp->stick) != 0)
    abort();
  if (pthread_mutex_unlock(&tmp->next->stick) != 0)
    abort();
  printf("\x1b[33mPhilosophe %d : J'ai arrêté de manger sa race\x1b[0m\n", tmp->id);
}

static void	think(philo *tmp)
{
  int	takenStick;

  takenStick = 0;
  if (tmp->prev->state == REST)
    {
      if (pthread_mutex_lock(&tmp->stick) != 0)
	abort();
      takenStick = 1;
    }
  else if (tmp->next->state == REST)
    {
      if (pthread_mutex_lock(&tmp->next->stick) != 0)
	abort();
      takenStick = 2;
    }
  tmp->state = THINK;
  printf("\x1b[35mPhilosophe %d : Je réfléchis enculé\x1b[0m\n", tmp->id);
  sleep(1);
  if (takenStick == 2)
    {
      if (pthread_mutex_lock(&tmp->stick) != 0)
	abort();
    }
  else
    {
      if (pthread_mutex_lock(&tmp->next->stick) != 0)
	abort();
    }
  eat(tmp);
}

void	*phil_acting(void *arg)
{
  philo	*tmp;
  int	bool = 0;
  
  tmp = arg;
  while (tmp->stock)
    {
      if (tmp->state == REST && bool == 0)
	{
	  printf("\x1b[29mPhilosophe %d : Je ne fais rien\x1b[0m\n", tmp->id);
	  bool = 1;
	}
      if (tmp->prev->state == REST && tmp->next->state == REST)
	{
	  if (pthread_mutex_lock(&tmp->stick) != 0)
	    abort();
	  if (pthread_mutex_lock(&tmp->next->stick) != 0)
	    abort();
	  eat(tmp);
	  bool = 0;
	}
      else if (tmp->prev->state == REST || tmp->next->state == REST)
	{
	  think(tmp);
	  bool = 0;
	}
    }
  return (arg);
}
