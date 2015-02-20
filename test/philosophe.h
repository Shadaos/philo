#ifndef PHILOSOPHE_H_
# define PHILOSOPHE_H_

# include <pthread.h>

typedef struct s_philo	*philo;
typedef enum eCondition	eCondition;
enum	eCondition
  {
    REST,
    THINK,
    EAT
  };

struct	s_philo
{
  pthread_t		unit;
  pthread_mutex_t	stick;
  eCondition		state;
  int			cycle_left;
  int			nb;
  philo			next;
  philo			prev;
};

#endif
