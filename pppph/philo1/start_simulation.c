#include  "philo.h"


void 	start_simulation(t_table *table )
{
	int  i =0;
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
	while ( table->simulation_running )
	{
		ft_usleep(100);
		if(table->meals_required != -1 )
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
				printf("			YES\n\n");
			// if(get_time() - table->philos[k].time >=  table->time_to_die)
			// {
			// 	table->a = 1;
			// 	table->philo_is_die = true;
			// 	pthread_mutex_lock(&table->print_is_die);

			// 	printf(RED "Time %u "RESET" | " YELLOW "Philo id = %d" RESET " | " CYAN "status : %s" RESET , 
			// 	get_time()- table->start_time, table->philos->id, "MAAAAAAAAT !!\n");

			// 	pthread_mutex_unlock(&table->print_is_die);
			// 	// ft_usleep(100);
			// 	// exit(1);
			// 	break;
			// }

		}
	
		int j = 0;
		while (j <  table->num_philo)
		{
			if(get_time() - table->philos[j].time >=  table->time_to_die)
			{
				// table->a = 1;
				table->philo_is_die = true;
				pthread_mutex_lock(&table->print_lock);

				printf(RED "Time %u "RESET" | " YELLOW "Philo id = %d" RESET " | " CYAN "status : %s" RESET ,
				get_time()- table->start_time, table->philos->id, "MAAAAAAAAT !!\n");
				pthread_mutex_unlock(&table->print_lock);

				// ft_usleep(100);
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

