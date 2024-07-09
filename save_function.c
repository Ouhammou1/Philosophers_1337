#include "philo.h"

void *safe_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if(!ptr)
		print_eror(" malloc error\n");
	
	return (ptr);
}

int ft_strcmp( char *s1,  char *s2)
{
	int i = 0;
	while(s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}


void save_metux_handle(pthread_mutex_t *mutex , char *s)
{
	if(	ft_strcmp(s, "lock") == 0)
		pthread_mutex_lock(mutex);

	else if(	ft_strcmp(s, "unlock") == 0)
		pthread_mutex_unlock(mutex);

	else if(ft_strcmp(s, "init") == 0)
	{
		if(pthread_mutex_init(mutex, NULL) != 0)
			print_eror("mutex init error\n");
	}
	else if(ft_strcmp(s, "destroy") == 0)
	{
		if(pthread_mutex_destroy(mutex) != 0)
			print_eror("mutex destroy error\n");
	}
	else
		print_eror("wrong mutex handle\n");
	
	printf("mutex %s\n", s);

}
