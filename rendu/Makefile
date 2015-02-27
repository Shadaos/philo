##
## Makefile for  in /home/beauch_a/rendu/PSU/PSU_2014_philo/philo/rendu
## 
## Made by Aurelien Beauchef
## Login   <beauch_a@epitech.net>
## 
## Started on  Fri Feb 27 14:25:24 2015 Aurelien Beauchef
## Last update Fri Feb 27 14:28:32 2015 Aurelien Beauchef
##

NAME	= philo

SRCS	= Philosophe.c \
	  init_list.c \
	  main.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	+= -Wall -Wextra -Werror

CC	= gcc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -lpthread

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
