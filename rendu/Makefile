NAME	= philo

SRCS	= Philosophe.c \
	  Print.c \
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
