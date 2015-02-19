#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "leHeader.h"



int	add_philo(philo *list, int nb)
{
  philo	new;
  philo	tmp;

  tmp = *list;
  if ((new = malloc(sizeof(struct s_philo))) == NULL)
    return (-1);
  new->nb = nb;
  new->condition = REST;
  new->next = NULL;
  while (tmp->next != NULL)
    tmp = tmp->next;
  if (tmp)
    tmp->next = new;
  new->prev = tmp;
  return (0);
}

void	do_clist(philo list)
{
  philo tmp;

  tmp = list;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = list;
}

int	main()
{
  philo	list_philo;
  int	nb_philo;

  nb_philo = 1;
  if ((list_philo = malloc(sizeof(struct s_philo))) == NULL)
    return (-1);
  list_philo->nb = 0;
  list_philo->condition = REST;
  while (nb_philo < PHILOSOPHE)
    {
      if ((add_philo(&list_philo, nb_philo)) == -1)
	return (-1);
      ++nb_philo;
    }
  do_clist(list_philo);
  /*
  while (list_philo != NULL)
  {
  printf("%d <- condition\n", (int)list_philo->condition);
  printf("%d <- NB\n", list_philo->nb);
  list_philo = list_philo->next;
  }
  */
  return (0);
}
