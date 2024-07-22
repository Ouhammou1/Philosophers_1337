#include "philo.h"


int main(int ac , char **av)
{
	t_table table;

	if(ac == 6 || ac == 5)
	{
		parsing_data(&table , ac, av);
		data_init(&table);
		start_simulation(&table);
	}
	else
		printf_error("Error: Wrong number of arguments !");

	return (0);
}