#include "philo.h"

void 	*philo_init( t_table  *table)
{	
	int  i =0;
	t_philo *philo;

	while ( i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i +1;
		philo->meals_count = 0;
		philo->full = false;
		philo->table  =table;
		
	}
	
}

void 	data_init(t_table *table)
{
	int i = 0;
	table->end_simalation = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);

	while (i < table->philo_nbr)
	{
		save_metux_handle(&table->forks[i].fork , "init");
		table->forks[i].fork_id = i;
		i++;
	}

	philo_init(table);
	
}