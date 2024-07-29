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
	while((get_time() - start) < time)
	{
		usleep(100);
	}
}

void 	print_output( t_philo *philo, char *status)
{
	// if(!philo->table->a)
	// {
		pthread_mutex_lock(&philo->table->print_lock);
		// printf(RED "Time %u "RESET" | " YELLOW "Philo id = %d" RESET " | " CYAN "status : %s" RESET " " MAGENTA" %d\n" RESET, get_time() - philo->table->start_time, philo->id, status, id_fork);
		printf("%u %d %s\n", get_time() - philo->table->start_time, philo->id, status);
		pthread_mutex_unlock(&philo->table->print_lock);
		
	// }
		// pthread_mutex_lock(&philo->table->print_lock);
		// printf(RED "Time %u "RESET" | " YELLOW "Philo id = %d" RESET " | " CYAN "status : %s" RESET " " MAGENTA" %d\n" RESET, get_time()- philo->table->start_time, philo->id, status, id_fork);
		// pthread_mutex_unlock(&philo->table->print_lock);
}

void print_is_die(t_table *table)
{
	pthread_mutex_lock(&table->print_lock);
	printf(RED "Time %u "RESET" | " YELLOW "Philo id = %d" RESET " | " CYAN "status : %s\n", get_time()- table->start_time, table->philos->id, "-<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>> is died");
	// exit(1);
	pthread_mutex_unlock(&table->print_lock);

}