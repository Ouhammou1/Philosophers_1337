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
			if (get_time() - get_long(&table->philos[i].time_mutex ,&table->philos[i].last_meal_time) >= table->time_to_die)
			{
				set_long(&table->stop_mutex , &table->simulation_running, 0);
				print_output(&table->philos[i], "died");
				return ;
			}
		}
	}
	// while ( table->simulation_running )
	// {
	// 	// printf("meals_eaten = %d \n", table->philos->meals_eaten);
	// 	ft_usleep(100);

	// 	if(table->meals_required != -1 )
	// 	{

	// 		while ( k < table->num_philo && table->philos[k].meals_eaten < table->meals_required )
	// 		{
	// 			printf("table->philo[%d].mleals = %d \t", k ,table->philos[k].meals_eaten);
	// 			printf("meals required = %d \n", table->meals_required);
	// 			// printf("table->philo[%d].mleals = %d \n", k ,table->philos[k].meals_eaten);
	// 			k++;
	// 		}
	// 		printf("k = %d \t\t num philo = %d \n", k , table->num_philo);
	// 		if( k == table->num_philo)
	// 		{
	// 			table->a = 1;
	// 			table->simulation_running = 0;
	// 			printf("OK\n");
	// 			break;
	// 		}
	// 			printf("			YES\n\n");
	// 		if(get_time() - table->philos[k].time >=  table->time_to_die)
	// 		{
	// 			table->a = 1;
	// 			table->philo_is_die = true;
	// 			pthread_mutex_lock(&table->print_is_die);

	// 			printf(RED "Time %u "RESET" | " YELLOW "Philo id = %d" RESET " | " CYAN "status : %s" RESET , 
	// 			get_time()- table->start_time, table->philos->id, "MAAAAAAAAT !!\n");

	// 			pthread_mutex_unlock(&table->print_is_die);
	// 			// ft_usleep(100);
	// 			// exit(1);
	// 			break;
	// 		}

		
	// 	}
	// 	// int j = 0;
	// 	// while (j <  table->num_philo)
	// 	// {
	// 	// 	if(get_time() - table->philos[j].time <  table->time_to_die)
	// 	// 	{
	// 	// 		// table->a = 1;
	// 	// 		table->simulation_running = 0;
	// 	// 		table->philo_is_die = true;
	// 	// 		pthread_mutex_lock(&table->print_lock);
	// 	// 		printf(RED "Time %u "RESET" | " YELLOW "Philo id = %d" RESET " | " CYAN "status : %s" RESET ,
	// 	// 		get_time()- table->start_time, table->philos->id, "MAAAAAAAAT !!\n\n");
	// 	// 		pthread_mutex_unlock(&table->print_lock);

	// 	// 		// ft_usleep(100);
	// 	// 		exit(1);
	// 	// 	}
	// 	// 	j++;
	// 	// }
	// 	}
	// // }
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
	ft_usleep(philo->table->time_to_eat);
	// philo->time = get_time();
	philo->last_meal_time = get_time();
	set_long(&philo->time_mutex, &philo->last_meal_time, get_time());

	// print_output(philo, "putting fork", philo->fork_id_left);
	// print_output(philo, "putting fork", philo->fork_id_right);

	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_right]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_left]);
	// printf("=================>>>>   meals_eaten  = %d\n", philo->meals_eaten);
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

