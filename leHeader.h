#ifndef LEHEADER_H_
# define LEHEADER_H_

# include <pthread.h>

# define PHILOSOPHE 7

typedef struct		s_philo
{
  pthread_t		philo;
  int			nb;
  pthread_mutex_t	stick;
  struct s_philo	*next;
}			philo;

#endif /* !LEHEADER_H_ */
