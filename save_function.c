#include "philo.h"

void *safe_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if(!ptr)
		print_eror(" malloc error\n");
	
	return (ptr);
}

void	handle_mutex(pthread_mutex_t *mutex)
{
	int c = pthread_mutex_init(mutex, NULL);
	if (  c != 0)
		print_eror("mutex init error\n");
}
