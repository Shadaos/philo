#include <pthread.h>
#include <stdlib.h>
#include <stdio.h> // PRINTF
#include "philosophe.h"

static void	*phil_acting(void *phil)
{
  philo	tmp;

  tmp = (philo)phil;
  
  printf("JE SUIS LE PHILOSOPHE %d\n", tmp->nb);
}

static int	add_phil(philo *list, int pos)
{
  philo	ret;
  philo	tmp;

  tmp = *list;
  if ((ret = malloc(sizeof(struct s_philo))) == NULL)
    return (-1);
  ret->nb = pos;
  printf("%p - %d \n", ret, ret->nb);
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

  nb_philo = 0;
  if  ((list_philo = welcome_philo(nb_eater)) == NULL)
    return (-1);
  while (nb_philo < nb_eater)
    {
      pthread_create(&list_philo->unit, NULL, phil_acting, list_philo);
      list_philo = list_philo->next;
      ++nb_philo;
    }
  sleep(10);
}

int	main()
{
  food_table(7);
  return (0);
}
