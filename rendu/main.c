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

static int	food_table(int nb_eater)
{
  philo		*list_philo;
  int		nb_philo;
  
  nb_philo = 0;
  if ((list_philo = welcome_philo(nb_eater)) == NULL)
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
  if (ac == 1)
    food_table(7);
  else
    food_table(atoi(av[1]));
  return (0);
}
