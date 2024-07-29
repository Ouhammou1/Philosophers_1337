#include  "philo.h"


void 	start_simulation(t_table *table )
{
	int  i =0;
	int ret;

	table->simulation_running = 1;
	table->start_time = get_time();
	
	while (i <  table->num_philo)
	{
		// ft_usleep(100);
		// printf("table->philos[%d].meals_eaten  == %ld\n", i , table->philos[i].last_meal_time);
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
			if(table->meals_required != -1)
			{
				if(table->philos[i].meals_eaten >= table->meals_required)
				{
					set_long(&table->stop_mutex , &table->simulation_running, 0);
					print_output(&table->philos[i], "----------->finished");
					return ;
				}
			}
			if (get_time() - get_long(&table->philos[i].time_mutex ,&table->philos[i].last_meal_time) >= table->time_to_die)
			{
				set_long(&table->stop_mutex , &table->simulation_running, 0);
				print_output(&table->philos[i], "died");
				return ;
			}
			i++;

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
	ft_usleep(philo->table->time_to_eat);

	set_long(&philo->time_mutex, &philo->last_meal_time, get_time());

	// philo->meals_eaten++;
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
	if (philo->id % 2 == 0)
		sleeping(philo);
	while (get_long(&philo->table->stop_mutex , &philo->table->simulation_running) )// && philo->meals_eaten <= philo->table->meals_required)
	{

		thinking(philo);
		eating(philo);	
		sleeping(philo);
		if(philo->table->meals_required != -1  && philo->meals_eaten +1 <= philo->table->meals_required)
		{
			increment(&philo->table->inct_meals_eaten , &philo->meals_eaten);
		}
		// philo->meals_eaten++;
	}
	return (NULL);
}

