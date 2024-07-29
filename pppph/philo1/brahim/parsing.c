#include "philo.h"

int	ft_isdigit(int c)

{
	if (c >= 48 && c <= 57)
	{ 
		return (1);
	}
	return (0);
}

void	parsing_data(t_table *table , int  ac , char **av)
{
	int  i=1;
	while (i < ac )
	{
		int j =0;
		while (av[i][j] != '\0')
		{
			if( ft_isdigit(av[i][j]) == 0)
				printf_error("Enter Numbers Please !");
			j++;
		}
		i++;
	}
	table->num_philo     = ft_atoi(av[1]);
	table->time_to_die   = ft_atoi(av[2]);
	table->time_to_eat   = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->meals_required = ft_atoi(av[5]);
	else
		table->meals_required = -1;
}

void		data_init( t_table  *table)
{
	int i;

	table->philos = save_memory(sizeof(t_philo) * table->num_philo);
	table->forks  = save_memory(sizeof(pthread_mutex_t) * table->num_philo);
	table->simulation_running = 1;
	table->philo_is_die = false;
	table->ready = false;

	
	pthread_mutex_init(&table->stop_mutex, NULL);
	pthread_mutex_init(&table->table_ready, NULL);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		printf_error("Mutex init of print_lock is failed");

	if(pthread_mutex_init(&table->print_is_die, NULL)!= 0)
		printf_error("Mutex init of print_lock is failed");

	
	i = 0;
	while (i < table->num_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = get_time();
		table->philos[i].table = table;
		table->philos[i].fork_id_left= i;
		table->philos[i].fork_id_right = (i + 1) % table->num_philo;
		table->philos[i].time = 0;
		// if(table->meals_required != -1)
		// 	table->philos[i].num_eat = meals_required;
		pthread_mutex_init(&table->philos[i].time_mutex, NULL);

		if (pthread_mutex_init(&table->forks[i], NULL) !=0)
			printf_error("Mutex init  of forks[i] is failed");	
		i++;
	}
	if ( pthread_mutex_init(&table->print_lock, NULL) !=0)
			printf_error("Mutex init  of forks[i] is failed");	
	
		// printffff(table);
}

// void 	printffff(t_table *table)
// {
// 	int i =0;
// 	printf("table num_philo = %d \n", table->num_philo);
// 	printf("table time to die = %u\n", table->time_to_die);
// 	printf("table time to est  = %u\n", table->time_to_eat);
// 	printf("table time to sleep = %u\n", table->time_to_sleep);
// 	printf("table meals reauired  = %d\n",  table->meals_required);
// 	printf("table philo = %p \n\n", table->philos);

// 	while (i  < table->num_philo)
// 	{
// 		printf("		philo id = %d \n", table->philos[i].id);
// 		printf("		philo meals_eaten = %d \n", table->philos[i].meals_eaten);
// 		printf("		philo last_meal_time = %ld \n", table->philos[i].last_meal_time);
// 		printf("		philo table = %p \n", table->philos[i].table);
// 		printf("		philo fork id left = %d \n", table->philos[i].fork_id_left);
// 		printf("		philo fork id right = %d \n", table->philos[i].fork_id_right);
// 		printf("		addres of mutex fork = %d || %p \n\n" , i , &table->forks[i]);
// 		i++;
// 	}
// }
