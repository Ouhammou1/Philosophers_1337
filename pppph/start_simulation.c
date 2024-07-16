#include  "philo.h"


void 	start_simulation(t_table *table )
{
	int  i =0;
	// int j =0;
	int k =0;
	table->a=0;
	int ret;
	table->simulation_running = 1;
	while (i <  table->num_philo)
	{
		ft_usleep(100);
		ret = pthread_create(&table->philos[i].thread, NULL , philo_life_cycle, &table->philos[i]);
		if(ret != 0)
			printf_error("Error creating thread");
		i++;
	}
	// while (table->simulation_running)// && table->philos[j].meals_eaten <= table->meals_required )
	// {
	// 	// printf("	YYYYYY TTTTTT YYYYY\n");
	// 	if(get_time() - table->time >= table->time_to_die)
	// 	{
	// 		printf("get_time = %u\ntable->time = %u\n ", get_time(), table->time);
	// 		printf("get_time() - table->time = %u\ntime_to_die = %u \n", get_time() - table->time , table->time_to_die);
	// 		print_output(table->philos , "is died", table->philos->id);
	// 		table->simulation_running =0;
	// 		break;
	// 	}
	// 	// j++;
	// }
	while ( table->simulation_running )
	{
		// while (j < table->num_philo  && table->philos[j].meals_eaten >= table->meals_required )
		// {
		// 	printf("	YYYYYY TTTTTT YYYYY\n");
		// 	if(get_time() - table->time >= table->time_to_die)
		// 	{
		// 		printf("get_time = %u\ntable->time = %u\n ", get_time(), table->time);
		// 		printf("get_time() - table->time = %u\ntime_to_die = %u \n", get_time() - table->time , table->time_to_die);
		// 		table->simulation_running =0;
		// 		print_output(table->philos , "-<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>> is died", table->philos->id);
		// 		break;
		// 	}
		// 	j++;
		// }
		ft_usleep(100);
		if(table->meals_required != -1)
		{
			while ( k < table->num_philo && table->philos[k].meals_eaten >= table->meals_required )
				k++;
			if( k == table->num_philo)
			{
				table->a = 1;
				table->simulation_running = 0;
				printf("OK\n");
				break;
			}

		}
	
		int j = 0;
		while (j <  table->num_philo)
		{
			// printf("get_time = %u\ntable->time = %u\n ", get_time(), table->philos[j].time);
			// printf("get_time() - table->time = %u\ntime_to_die = %u \n", get_time() - table->philos[j].time , table->time_to_die);
			if(get_time() - table->philos[j].time >=  table->time_to_die)
			{
				printf("\n    KILL KILL KILL ---> \n\n");
				table->philo_is_die = true;
				// print_is_die(table);
				print_output(table->philos, "IMOT AWA IMOT !!!!!!!!", table->philos->id);
				table->a = 1;
				ft_usleep(100);
				exit(1);
			}
			j++;
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
	pthread_mutex_lock(&philo->table->forks[philo->fork_id_right]);

	print_output(philo, "taking fork", philo->fork_id_left);
	print_output(philo, "taking fork", philo->fork_id_right);


	print_output(philo, "🍽️  is eating", 0);
	philo->time = get_time();
	ft_usleep(philo->table->time_to_eat);


	print_output(philo, "putting fork", philo->fork_id_left);
	print_output(philo, "putting fork", philo->fork_id_right);

	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_left]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_right]);
	philo->meals_eaten++;
	// printf("meals_eaten  = %d\n", philo->meals_eaten);
}


void	sleeping( t_philo *philo)
{
	print_output(philo, "🥱  is sleeping", 0);
	ft_usleep(philo->table->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_output(philo, "🤔  is thinking", 0);
	ft_usleep(philo->table->time_to_sleep);
}


void	*philo_life_cycle(void *data)
{

	t_philo *philo = (t_philo *)data;
	while (philo->table->simulation_running != 0 && philo->table->philo_is_die == false )
	{
		eating(philo);	
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

