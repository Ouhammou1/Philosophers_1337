#include "philo.h"

void	printf_error(char 	*str)
{
	printf(RED "%s\n" RESET, str);
	exit(1);
}

void 	*save_memory(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if(!ptr)
		printf_error("Malloc failed");
	return (ptr);
}

unsigned int  get_time()
{
	struct timeval av;	
	gettimeofday(&av  ,NULL);
	return ( (av.tv_sec * 1000) + (av.tv_usec / 1000));
}

 void ft_usleep(unsigned int time)
{
	unsigned int start = get_time();
	while (get_time() - start < time)
	{
		usleep(100);
	}
}

void 	print_output( t_philo *philo, char *status, int id_fork)
{
	printf(RED "Time %u "RESET" | " YELLOW "Philo id = %d" RESET " | " CYAN "status : %s %d\n" RESET, get_time()- philo->table->start_time, philo->id, status, id_fork);
}