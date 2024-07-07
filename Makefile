CC =CC
CFLAGS= -Wall -Wextra -Werror
CFILES= parsing.c philo.c utils.c data_init.c 

OBJS= $(CFILES:.c=.o)
NAME = philo


all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re: fclean all 
