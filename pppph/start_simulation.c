#include  "philo.h"

void 	start_simulation(t_table *table )
{
	int  i =0;
	int ret;
	while (i <  table->num_philo)
	{
		ret = pthread_create(&table->philos[i].thread, NULL , philo_life_cycle, &table->philos[i]);
		if(ret != 0)
			printf_error("Error creating thread");
		
		// printf("ret = %d  	|| 		num of the philo = %d \n", ret , table->philos[i].id);
		i++;
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


	printf("Time %u  | Philo id = %d | status : %s  %d \n", get_time(), philo->id , "taking fork", philo->fork_id_left);
	printf("Time %u  | Philo id = %d | status : %s  %d \n", get_time(), philo->id , "taking fork", philo->fork_id_right);


	unsigned int  start =  get_time();
	unsigned int  tmp   =  get_time();
	// printf("\n\n\n BM tmp = %u  \n  start =  %u \n tmp - start = %u \n time to eat = %d \n\n\n",tmp, start , tmp - start ,philo->table->time_to_eat);

	while (tmp - start <= philo->table->time_to_eat)
	{
		tmp = get_time();
		printf("Time %u  | Philo id = %d | status : %s  \n", get_time(), philo->id , "is eating");
		usleep(150000);
	}


	printf("time %u  | Philo id = %d | status : %s  %d \n", get_time(), philo->id , "putting  fork", philo->fork_id_left);
	printf("time %u  | Philo id = %d | status : %s  %d \n", get_time(), philo->id , "putting fork", philo->fork_id_right);


	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_left]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_right]);
}



void	*philo_life_cycle(void *data)
{
	char *ptr = "One philo is eating\n";

	t_philo *philo = (t_philo *)data;
	eating(philo);	

	// printf("\n\n\n  get_time = %lld  \n  start =  %lld \n  time to die = %ld \n",get_time() , start , philo->table->time_to_die);

	return (ptr);
}

