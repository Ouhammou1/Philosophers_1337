#include "philo.h"

void	parsing_data(t_table *table ,char **av)
{
	table->num_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->meals_required = ft_atoi(av[5]);
	else
		table->meals_required = 0;
	


}

void		data_init( t_table  *table)
{
	int i;

	table->philos = save_memory(sizeof(t_philo) * table->num_philo);
	table->forks = save_memory(sizeof(pthread_mutex_t) * table->num_philo);

	i = 0;
	while (i < table->num_philo)
	{
		table->philos[i].id = i ;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].table = table;
		table->philos[i].fork_id_left= i;
		table->philos[i].fork_id_right = (i + 1) % table->num_philo;
		if ( pthread_mutex_init(&table->forks[i], NULL) !=0)
			printf_error("Mutex init  of forks[i] is failed");	

		i++;
	}
		printffff(table);
}

void 	printffff(t_table *table)
{
	int i =0;
	printf("table num_philo = %d \n", table->num_philo);
	printf("table time to die = %ld\n", table->time_to_die);
	printf("table time to est  = %ld\n", table->time_to_eat);
	printf("table time to sleep = %ld\n", table->time_to_sleep);
	printf("table meals reauired  = %d\n",  table->meals_required);
	printf("table philo = %p \n\n", table->philos);

	while (i  < table->num_philo)
	{
		printf("		philo id = %d \n", table->philos[i].id);
		printf("		philo meals_eaten = %d \n", table->philos[i].meals_eaten);
		printf("		philo last_meal_time = %ld \n", table->philos[i].last_meal_time);
		printf("		philo table = %p \n", table->philos[i].table);
		printf("		philo fork id left = %d \n", table->philos[i].fork_id_left);
		printf("		philo fork id right = %d \n", table->philos[i].fork_id_right);
		printf("		addres of mutex fork = %d || %p \n\n" , i , &table->forks[i]);
		i++;
	}
}




// int i =0;
// 		printf("table num_philo = %d\n", table->num_philo);
// 		printf("table time_to_die = %ld\n", table->time_to_die);
// 		printf("table time_to_eat = %ld\n", table->time_to_eat);
// 		printf("table time_to_sleep = %ld\n", table->time_to_sleep);
// 		printf("table meals_required = %d\n\n", table->meals_required);
// 		while (i < table->num_philo)
// 		{
// 			printf("		philo id = %d\n", table->philos[i].id);
// 			printf("		philo meals_eaten = %d\n", table->philos[i].meals_eaten);
// 			printf("		philo last_meal_time = %ld\n", table->philos[i].last_meal_time);
// 			printf("		philo table = %p\n", table->philos[i].table);
// 			printf("		philo fork_id_left = %d\n", table->philos[i].fork_id_left);
// 			printf("		philo fork_id_right = %d\n\n", table->philos[i].fork_id_right);

// 			i++;
// 		}


