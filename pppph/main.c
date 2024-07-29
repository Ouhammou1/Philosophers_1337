#include "philo.h"


int main(int ac , char **av)
{
	t_table table;

	if(ac == 6 || ac == 5)
	{
		parsing_data(&table , ac, av);
		data_init(&table);
		start_simulation(&table);
	int l = 0;
	while ( l < table.num_philo)
	{
		pthread_join(table.philos[l].thread , NULL);
		l++;	
	}
	}
	else
		printf_error("Error: Wrong number of arguments !");

	return (0);
}