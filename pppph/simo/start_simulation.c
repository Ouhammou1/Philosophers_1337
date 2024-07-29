#include  "philo.h"


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

// void increment(pthread_mutex_t *mutex, int *val)
// {
// 	pthread_mutex_lock(mutex);
// 	(*val)++;
// 	printf("val---------------------------------------->>>>  = %d\n",*(int *)val);
// 	pthread_mutex_lock(mutex);

// }

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
void 	start_simulation(t_table *table )
{
	int  i =0;
	// int k =0;
	table->a=0;
	int ret;
	table->simulation_running = 1;
	table->start_time = get_time();
	while (i <  table->num_philo)
	{
		// ft_usleep(100);
		ret = pthread_create(&table->philos[i].thread, NULL , philo_life_cycle, &table->philos[i]);
		if(ret != 0)
			printf_error("Error creating thread");
		i++;
	}
	set_bool(&table->table_ready, &table->ready, true);
	while (1)
	{
		i = 0;
		while (i < table->num_philo)
		{
			// if (get_time() - get_long(&table->philos[i].time_mutex ,&table->philos[i].last_meal_time) >= table->time_to_die)
			if(get_time() - table->philos[i].last_meal_time >= table->time_to_die)
			{
				
				// set_long(&table->stop_mutex , &table->simulation_running, 0);
				table->simulation_running = 0;
				print_output(&table->philos[i], "died");
				return ;
			}

			i++;
			// while ( k < table->num_philo && table->philos[k].meals_eaten < table->meals_required )
			// {
			// 	printf("\n\ntable->philos[%d].meals_eaten = %d \n\n", table->philos->id ,table->philos[k].meals_eaten);
			// 	printf("\n\ntable->meals_required  = %d \n", table->meals_required );
			// 	increment(&table->incr , &k);
			// }

			// // printf("k = %d \n", k);
			// if( k == table->num_philo)
			// {
			// 	set_long(&table->stop_mutex, &table->simulation_running , 0);
			// 	printf("OK\n");
			// 	return;
			// }
		}
		if(table->meals_required != -1)
		{
			// printf("---> \n");
			// exit(0);
			i = 0;
			int counter = 0;
			while(i < table->num_philo)
			{
				if(table->philos[i].meals_eaten >= table->meals_required)
					counter++;
				i++;
			}
			if(counter == table->num_philo)
			{
				printf("-----------> all ate\n");
				exit(1);
			}
		}
	}
	
	int l = 0;
	while ( l < table->num_philo)
	{
		pthread_join(table->philos[l].thread , NULL);
		l++;	
	}
}



void eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->fork_id_left]);
	print_output(philo, "has taken a fork");

	pthread_mutex_lock(&philo->table->forks[philo->fork_id_right]);
	print_output(philo, "has taken a fork");


	print_output(philo, "is eating");
	philo->last_meal_time = get_time();
	ft_usleep(philo->table->time_to_eat);
	// philo->time = get_time();
	// set_long(&philo->time_mutex, &philo->last_meal_time, get_time());

	philo->meals_eaten++;
	// printf("\n\nGGGG\n");
	
	// increment(&philo->table->inct_meals_eaten , &philo->meals_eaten);

	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_right]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_left]);
}


void	sleeping( t_philo *philo)
{
	print_output(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_output(philo, "is thinking");
	// ft_usleep(philo->table->time_to_sleep);
}

void	*philo_life_cycle(void *data)
{

	t_philo *philo = (t_philo *)data;
	while (!get_bool(&philo->table->table_ready, &philo->table->ready))
	;
	if (philo->id % 2 != 0)
		sleeping(philo);
	while (get_long(&philo->table->stop_mutex , &philo->table->simulation_running) != 0 )//&& philo->table->philo_is_die == false )
	{
		// printf("dfgh\n");
		thinking(philo);
		eating(philo);	
		sleeping(philo);
	}
	return (NULL);
}

