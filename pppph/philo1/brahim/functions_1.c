#include  "philo.h"

void increment(pthread_mutex_t *mutex, int *val)
{
	pthread_mutex_lock(mutex);
	(*val)++;
	printf("====================<><><><>>>>>>>>>>>>>>>   val = %d \n ", *(int *)val);
	pthread_mutex_lock(mutex);
}

bool get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool res;
	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

long get_long(pthread_mutex_t *mutex, long *value)
{
	long res;
	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}


void set_long(pthread_mutex_t *mutex,long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}
void set_bool(pthread_mutex_t *mutex,bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}