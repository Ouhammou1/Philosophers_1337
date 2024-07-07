#include "philo.h"

void	parse_input( t_table *table ,char **av)
{
	table->philo_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]) * 1000;
	table->time_to_est = ft_atoi(av[3]) * 1000;
	table->time_to_sleep = ft_atoi(av[4]) * 1000;

	if(table->time_to_die< 60000 || table->time_to_est < 60000 || table->time_to_sleep  < 60000)
		print_eror("Error: Time must be greater than 60ms\n");

	if(av[5])
		table->meals_nbr = ft_atoi(av[5]);
	else
		table->meals_nbr = -1;

	

	printf("philo_nbr = %ld\n", table->philo_nbr);

}
