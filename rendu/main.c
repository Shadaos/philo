#include <pthread.h>
#include <stdlib.h>
#include "Philosophe.h"

static void	join_philo(philo *list_philo, int nb_eater)
{
  int		nb_philo;

  nb_philo = 0;
  while (nb_philo < nb_eater)
    {
      pthread_join(list_philo->unit, NULL);
      list_philo = list_philo->next;
      ++nb_philo;
    }
}

static int	food_table(int nb_eater, int nb_stock)
{
  philo		*list_philo;
  int		nb_philo;
  
  nb_philo = 0;
  if ((list_philo = welcome_philo(nb_eater, nb_stock)) == NULL)
    return (-1);
  while (nb_philo < nb_eater)
    {
      pthread_create(&list_philo->unit, NULL, phil_acting, list_philo);
      list_philo = list_philo->next;
      ++nb_philo;
    }
  join_philo(list_philo, nb_eater);
  return (0);
}

int	main(int ac, char **av)
{
  int	nb_philo;
  int	nb_stock;

  nb_stock = 0;
  nb_philo = 0;
  if (ac == 1)
    food_table(7, 5);
  else
    {
      nb_philo = atoi(av[1]);
      nb_stock = atoi(av[2]);
      if (nb_philo > 0 && nb_stock > 0)
	food_table(nb_philo, nb_stock);
      else
	food_table(7, 5);
    }
  return (0);
}
