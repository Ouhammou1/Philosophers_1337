#include  "philo.h"


void 	start_simulation(t_table *table )
{
	int  i =0;
	int ret;
	table->simulation_running = 1;
	while (i <  table->num_philo)
	{
		ret = pthread_create(&table->philos[i].thread, NULL , philo_life_cycle, &table->philos[i]);
		if(ret != 0)
			printf_error("Error creating thread");
		i++;
	}
	while ( table->simulation_running)
	{
		ft_usleep(100);
		i = 0;
		if(table->meals_required != -1)
		{
			while ( i < table->num_philo && table->philos[i].meals_eaten >= table->meals_required )
				i++;
			if ( i == table->num_philo)
			{
				table->simulation_running = 0;
				printf("OK\n");
				break;
			}
		}
	}
	int j = 0;
	while ( j < table->num_philo)
	{
		pthread_join(table->philos[j].thread , NULL);
		j++;	
	}
}



void eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->fork_id_left]);
	pthread_mutex_lock(&philo->table->forks[philo->fork_id_right]);

	print_output(philo, "taking fork", philo->fork_id_left);
	print_output(philo, "taking fork", philo->fork_id_right);


	print_output(philo, "🍽️  is eating", 0);
	ft_usleep(philo->table->time_to_eat);


	print_output(philo, "putting fork", philo->fork_id_left);
	print_output(philo, "putting fork", philo->fork_id_right);

	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_left]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_right]);
	philo->meals_eaten++;
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
	while (philo->table->simulation_running)
	{
		eating(philo);	
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

