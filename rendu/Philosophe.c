/*
** Philosophe.c for  in /home/beauch_a/rendu/PSU/PSU_2014_philo/philo/rendu
** 
** Made by Aurelien Beauchef
** Login   <beauch_a@epitech.net>
** 
** Started on  Fri Feb 27 14:25:40 2015 Aurelien Beauchef
** Last update Fri Feb 27 14:29:46 2015 Aurelien Beauchef
*/

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "Philosophe.h"

static void	eat(philo *tmp)
{
  tmp->state = EAT;
  tmp->stock = tmp->stock - 1;
  printf("\x1b[32mPhilosophe %d : Je mange\x1b[0m\n", tmp->id);
  sleep(2);
  tmp->state = REST;
  if (pthread_mutex_unlock(&tmp->stick) != 0)
    abort();
  if (pthread_mutex_unlock(&tmp->next->stick) != 0)
    abort();
  printf("\x1b[29mPhilosophe %d : Je ne fais rien\x1b[0m\n", tmp->id);
}

static void	get_other_stick(philo *tmp, int takenStick)
{
  if (takenStick == 2)
    {
      if (pthread_mutex_lock(&tmp->stick) != 0)
	abort();
    }
  else
    if (pthread_mutex_lock(&tmp->next->stick) != 0)
      abort();
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
  printf("\x1b[35mPhilosophe %d : Je réfléchis\x1b[0m\n", tmp->id);
  sleep(1);
  get_other_stick(tmp, takenStick);
  eat(tmp);
}

void	*phil_acting(void *arg)
{
  philo	*tmp;

  tmp = arg;
  printf("\x1b[29mPhilosophe %d : Je ne fais rien\x1b[0m\n", tmp->id);
  while (tmp->stock)
    {
      if (tmp->prev->state == REST && tmp->next->state == REST)
	{
	  if (pthread_mutex_lock(&tmp->stick) != 0)
	    abort();
	  if (pthread_mutex_lock(&tmp->next->stick) != 0)
	    abort();
	  eat(tmp);
	}
      else if (tmp->prev->state == REST || tmp->next->state == REST)
	think(tmp);
    }
  return (arg);
}
