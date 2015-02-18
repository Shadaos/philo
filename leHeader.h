#ifndef LEHEADER_H_
# define LEHEADER_H_

# include <pthread.h>

# define PHILOSOPHE 7

typedef struct s_philo	*philo;

struct		s_philo
{
  pthread_t		philo;
  int			nb;
  pthread_mutex_t	stick;
  philo			next;
};

#endif /* !LEHEADER_H_ */
