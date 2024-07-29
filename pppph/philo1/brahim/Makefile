CC =cc 
CFLAGS= -Wall -Wextra -Werror
CFILES= parsing.c main.c  ft_atoi.c functions.c start_simulation.c functions_1.c 

OBJS= $(CFILES:.c=.o)
NAME = philo


all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re: fclean all 
