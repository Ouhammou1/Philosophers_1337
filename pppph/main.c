#include "philo.h"


int main(int ac , char **av)
{
	t_table table;

	if(ac == 6 || ac == 5)
	{
		parsing_data(&table , av);
		data_init(&table);
	}
	else
		printf_error("Error: Wrong number of arguments\n");

	return (0);
}