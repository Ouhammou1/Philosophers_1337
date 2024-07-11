#include "philo.h"

void	printf_error(char 	*str)
{
	printf("%s\n", str);
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
// void	print_status(t_philo *philo , char *status , int id_fork)
// {
// 	long long int time;
// 	time =  get_time();
// 	pthread_mutex_lock(&philo->table->print_lock);
// 	printf("time %lld | Philo id = %d | status %s\n", time, philo->id , status);
// 	pthread_mutex_unlock(&philo->table->print_lock);
// }
 