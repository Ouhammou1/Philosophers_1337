#include "philo.h"

int main(int ac , char **av)
{
	if(ac == 6 || ac  == 5)
	{
		t_table table;

		parse_input(&table , av);

		data_init(&table);

		// dinner_start(&table);
		// clean(&table);
	}
	else
		print_eror("Error: Wrong number of arguments\n");
	return (0);
}