#include <pthread.h>
#include <stdlib.h>
#include <stdio.h> // PRINTF
#include "philosophe.h"


static void	to_eat(philo unit)
{
  printf("%d :---> eat\n", unit->nb); 
}

static void	to_rest(philo unit)
{
  printf("%d :---> rest\n", unit->nb); 
}

static void	to_think(philo unit)
{
  printf("%d :---> think\n", unit->nb); 
}

static void	*phil_print(void *phil)
{
  int	c = 0;
  int	nb_philo;
  philo	tmp;

  tmp = (philo)phil;

  while (c < 5) /* 5 == nombre de tour */
    {
      nb_philo = 0;
      
      while (nb_philo < 7) /* 7 == nombre de philo */
	{
	  //printf("nb : %d ----  state : %d\n", tmp->nb, tmp->state);
	  
	  if (tmp->state == EAT)
	    to_eat(tmp);
	  else if (tmp->state == REST)
	    to_rest(tmp);
	  else if (tmp->state == THINK)
	    to_think(tmp);
	  
	  tmp = tmp->next;
	  ++nb_philo;
	  }
      sleep(1);
      printf("------------------------------\n");
      c++;
    }
}

static void	*phil_acting(void *phil)
{
  philo	tmp;

  tmp = (philo)phil;

  int c = 0;
  
  while (c < 5)
    {
      if (tmp->state == REST)
	{
	  if ((tmp->next->state == REST && tmp->prev->state == REST) && (pthread_mutex_trylock(&(tmp->stick)) == 0 && pthread_mutex_trylock(&(tmp->next->stick)) == 0))
	    {
	      printf("Je suis le philosophe n %d et je commence à manger\n", tmp->nb);
	      tmp->state = EAT;
	      sleep(1);
	    }
	  else if ((tmp->next->state == REST || tmp->prev->state == REST) &&  (pthread_mutex_trylock(&(tmp->stick)) == 0 || pthread_mutex_trylock(&(tmp->next->stick)) == 0))
	    {
	      printf("Je suis le philosophe n %d et je commence à réfléchir\n", tmp->nb);
	      tmp->state = THINK;
	      sleep(1);
	    }
	  else
	    {
	      printf("Je suis le philosophe n %d et je me repose\n", tmp->nb);
	      tmp->state = REST;
	      sleep(1);
	    }
	}
      else if (tmp->state == THINK)
	{
	  if (pthread_mutex_trylock(&(tmp->stick)) == 0 || pthread_mutex_trylock(&(tmp->next->stick)) == 0)
	    {
	      printf("Je suis le philosophe n %d et j'arrete de reflechir pour manger\n", tmp->nb);
	      tmp->state = EAT;
	      sleep(1);
	    }
	  else
	    {
	      printf("PROBLEM THINK TO EAT PHILO NB -> %d\n", tmp->nb);
	      sleep(1);
	    }
	}
      else
	{
	  printf("Je suis le philosophe n %d et j'arrete de manger pour me reposer\n", tmp->nb);
	  pthread_mutex_unlock(&(tmp->stick));
	  pthread_mutex_unlock(&(tmp->next->stick));
	  tmp->state = REST;
	  sleep(1);
	}
      /*if (pthread_mutex_trylock(&(tmp->stick)) == 0 && pthread_mutex_trylock(&(tmp->next->stick)) == 0 && (tmp->prev->state != EAT))
	{
	  tmp->state = EAT;
	  sleep(1);
	}
      else if ((pthread_mutex_trylock(&(tmp->stick)) == 0 || pthread_mutex_trylock(&(tmp->next->stick)) == 0)
	       && (tmp->prev->state != THINK && tmp->prev->state != EAT))
	{
	  tmp->state = THINK;
	  sleep(1);
	}
      else if (tmp->state != THINK)
	{
	      pthread_mutex_unlock(&(tmp->stick));
	      pthread_mutex_unlock(&(tmp->next->stick));
	  tmp->state = REST;
	  sleep(1);
	  }*/
      
      /*
      if (tmp->state == THINK)
	{
	  if ((pthread_mutex_trylock(&(tmp->stick)) == 0 || pthread_mutex_trylock(&(tmp->next->stick)) == 0)
	      && (tmp->next->state != THINK && tmp->prev->state != THINK))
	    {
	      //printf("-----nb    EAT : %d----\n", tmp->nb);
	      tmp->state = EAT;
	      sleep(1);
	    }
	  else
	    {
	      sleep(1);
	    }
	}
      else
	{
	  //printf("JE SUIS LE PHILOSOPHE %d\n", tmp->nb);
	  
	  if (pthread_mutex_trylock(&(tmp->stick)) == 0 && pthread_mutex_trylock(&(tmp->next->stick)) == 0
	      && (tmp->next->state != THINK || tmp->prev->state != THINK))
	    {
	      //printf("-----nb    EAT : %d----\n", tmp->nb);
	      tmp->state = EAT;
	      sleep(1);
	      }
	  else if ((pthread_mutex_trylock(&(tmp->stick)) == 0)
		   && (tmp->prev->state != THINK && tmp->prev->state != EAT))
	    {
	      printf("-----nb Gauche  : %d----\n", tmp->nb);
	      tmp->state = THINK;
	      sleep(1);
	    }
	  else if ((pthread_mutex_trylock(&(tmp->next->stick)) == 0
	       || (pthread_mutex_trylock(&(tmp->stick)) == 0))
	      && tmp->prev->state != THINK
	      && tmp->next->state != THINK)
	    {
	      //printf("-----nb Droit  : %d----\n", tmp->nb);
	      tmp->state = THINK;
	      sleep(1);
	      //pthread_mutex_unlock(&(tmp->next->stick));
	    }
	  else if (tmp->state != THINK)
	    {
	      //printf("-----nb   Rest : %d----\n", tmp->nb);
	      tmp->state = REST;
	      sleep(1);
	      pthread_mutex_unlock(&(tmp->stick));
	      pthread_mutex_unlock(&(tmp->next->stick));
	    }
	}
      */
      c = c + 1;
    }
}

static int	add_phil(philo *list, int pos)
{
  philo	ret;
  philo	tmp;

  tmp = *list;
  if ((ret = malloc(sizeof(struct s_philo))) == NULL)
    return (-1);
  ret->nb = pos;
  //printf("%p - %d \n", ret, ret->nb);
  ret->state = REST;
  ret->next = NULL;
  if (tmp)
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = ret;
      ret->prev = tmp;
    }
  else
    ret->prev = NULL;
  return (0);
}

static void	circle_list(philo list)
{ 
  philo	tmp;

  tmp = list;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = list;
  list->prev = tmp;
}

static philo	welcome_philo(int nb_eater)
{
  philo	ret;
  int	nb;
  
  nb = 1;
  if ((ret = malloc(sizeof(struct s_philo))) == NULL)
    return (NULL);
  ret->nb = 0;
  ret->state = REST;
  ret->next = NULL;
  while (nb < nb_eater)
    {
      if ((add_phil(&ret, nb)) == -1)
	return (NULL);
      ++nb;
    }
  circle_list(ret);
  return (ret);
}

int	food_table(int nb_eater)
{
  philo	list_philo;
  int	nb_philo;
  pthread_t print;

  nb_philo = 0;
  if  ((list_philo = welcome_philo(nb_eater)) == NULL)
    return (-1);
  while (nb_philo < nb_eater)
    {
      pthread_create(&list_philo->unit, NULL, phil_acting, list_philo);
      list_philo = list_philo->next;
      ++nb_philo;
      /*      if (nb_philo == nb_eater)
	      pthread_create(&print, NULL, phil_print, list_philo);*/
    }

  nb_philo = 0;
  while (nb_philo < nb_eater)
    {
      pthread_join(list_philo->unit, NULL);
      list_philo = list_philo->next;
      ++nb_philo;
    }
  //  pthread_join(print, NULL);
}

int	main()
{
  food_table(7);
  return (0);
}
