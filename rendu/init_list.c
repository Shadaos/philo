#include <stdlib.h>
#include "Philosophe.h"

static int	add_phil(philo **list, int pos, int nb_stock)
{
  philo		*ret;
  philo		*tmp;

  tmp = *list;
  if ((ret = malloc(sizeof(struct s_philo))) == NULL)
    return (-1);
  ret->id = pos;
  ret->stock = nb_stock;
  ret->state = REST;
  pthread_mutex_init(&(ret->stick), NULL);
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

philo		*welcome_philo(int nb_eater, int nb_stock)
{
  philo		*ret;
  philo		*tmp;
  int		count;

  count = 1;
  if ((ret = malloc(sizeof(struct s_philo))) == NULL)
    return (NULL);
  ret->id = 0;
  ret->state = REST;
  ret->stock = nb_stock;
  pthread_mutex_init(&(ret->stick), NULL);
  ret->next = NULL;
  while (count < nb_eater)
    {
      if ((add_phil(&ret, count, nb_stock)) == -1)
	return (NULL);
      ++count;
    }
  tmp = ret;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = ret;
  ret->prev = tmp;
  return (ret);
}
