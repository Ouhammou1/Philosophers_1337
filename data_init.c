#include "philo.h"

void 	data_init(t_table *table)
{
	int i = 0;
	table->end_simalation = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);

	while (i < table->philo_nbr)
	{
		handle_mutex(&table->forks[i].fork);
		table->forks[i].fork_id = i;
		i++;
	}
	
}