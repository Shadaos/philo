/*
** Philosophe.h for  in /home/beauch_a/rendu/PSU/PSU_2014_philo/philo/rendu
** 
** Made by Aurelien Beauchef
** Login   <beauch_a@epitech.net>
** 
** Started on  Fri Feb 27 14:25:45 2015 Aurelien Beauchef
** Last update Fri Feb 27 14:25:46 2015 Aurelien Beauchef
*/

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

philo	*welcome_philo(int nb_eater, int nb_stock);
void	*phil_acting(void *arg);

#endif /* !PHILOSOPHE_H_ */
