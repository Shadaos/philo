#include <unistd.h>
#include <stdio.h>
#include "Philosophe.h"

void	*print_table(void *arg)
{
  philo	*tmp;
  int	nb_philo;
  int	count;

  tmp = arg;
  count = 0;
  while (count < 5)
    {
      nb_philo = 0;
      while (nb_philo < 7)
	{
	  if (tmp->state == EAT)
	    printf("\x1B[31mPhilosophe %d -> MANGE \n", tmp->id);
	  else if (tmp->state == THINK)
	    printf("\x1B[34mPhilosophe %d -> REFLECHIS\n", tmp->id);
	  else
	    printf("\x1B[32mPhilosophe %d -> DORS\n", tmp->id);
	    tmp = tmp->next;
	  ++nb_philo;
	}
        printf("\x1B[0m-------------------------\n");
      ++count;
      sleep(2);
    }
  return arg;
}
