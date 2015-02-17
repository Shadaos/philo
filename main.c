#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "leHeader.h"

int		add_philo(philo **list, int c)
{
  philo		*new_philo;
  philo		*tmp;

  if ((new_philo = malloc(sizeof(philo*))) == NULL)
    return (1);
  new_philo->nb = c;
  new_philo->next = NULL;
  tmp = *list;
  while (tmp->next == NULL)
    {
      tmp = tmp->next;
    }
  new_philo->next = tmp;
  return (0);
}

void		do_circle(philo **list)
{
  philo		*tmp;

  tmp = *list;
  while (tmp->next == NULL)
    {
      tmp = tmp->next;
    }
  (*list)->next = tmp;
}

int		main()
{
  int		c;
  philo		*list_philo;

  c = 0;
  if ((list_philo = malloc(sizeof(philo **))) == NULL)
    return (1);
  while (c < PHILOSOPHE)
    {
      if ((add_philo(&list_philo, c)) == 1)
	return (1);
      c = c + 1;
    }
  do_circle(&list_philo);
  while (list_philo != NULL)
    {
      printf("*** %d\n", list_philo->nb);
      list_philo = list_philo->next;
    }
  return (0);
}
