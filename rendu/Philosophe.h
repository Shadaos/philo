#ifndef PHILOSOPHE_H_
# define PHILOSOPHE_H_

# include <pthread.h>

# define TRUE 1
# define FALSE 0

typedef enum eCondition eCondition;
typedef struct s_philo	philo;
enum eCondition
  {
    REST,
    THINK,
    EAT
  };

struct			s_philo
{
  pthread_t		unit;
  pthread_mutex_t	stick;
  eCondition		state;
  int			stock;
  int			id;
  philo			*next;
  philo			*prev;
};

philo	*welcome_philo(int nb_eater);
void	*phil_acting(void *arg);
void	*print_table(void *arg);

#endif /* !PHILOSOPHE_H_ */
