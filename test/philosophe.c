#include <pthread.h>
#include <stdlib.h>
#include <stdio.h> // Printf

#include "philosophe.h"

void	*phil_acting(void *phil)
{
  philo	tmp;

  tmp = (philo)phil;
 
  printf("JE SUIS LE PHILOSOPHE %d\n", tmp->nb);
  sleep(4);
}

int	add_phil(philo *list, int pos)
{
  philo ret;
  philo tmp;

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

void	circle_list(philo list)
{
  philo	tmp;

  tmp = list;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = list;
  list->prev = tmp;
}
int	food_table(int nb_eater)
{
  philo	list_philo;
  int	nb_philo;

  nb_philo = 1;
  if ((list_philo = malloc(sizeof(struct s_philo))) == NULL)
    return (-1);
  list_philo->nb = 0;
  list_philo->state = REST;
  list_philo->next = NULL;
  while (nb_philo < nb_eater)
    {
      if ((add_phil(&list_philo, nb_philo)) == -1)
	return (-1);
      ++nb_philo;
    }
  circle_list(list_philo);
  nb_philo = 0;
  while (nb_philo < nb_eater)
    {
      printf("%d - nb \n", list_philo->nb);
      pthread_create(&list_philo->unit, NULL, phil_acting, list_philo);
      list_philo = list_philo->next;
      ++nb_philo;
    }
  sleep(1); // JOIN THREAD
}

int	main(int ac, char **av)
{
  if (ac == 1)
    {
      if (food_table(7) == -1)
	return (-1); // ERROR
    }
  else if (ac == 2)
    {
      if (food_table(atoi(av[1])) == -1)
	  return (-1); // ERROR
    }
  return (0);
}
