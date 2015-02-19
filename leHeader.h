#ifndef LEHEADER_H_
# define LEHEADER_H_

# include <pthread.h>

# define PHILOSOPHE 7

typedef struct s_philo	*philo;

typedef enum	eCondition eCondition;
enum		eCondition
  {
    REST,
    THINK,
    EAT
  };

struct		s_philo
{
  pthread_t		philo;
  eCondition		condition;
  int			nb;
  pthread_mutex_t	stick;
  philo			next;
};

#endif /* !LEHEADER_H_ */
