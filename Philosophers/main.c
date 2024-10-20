/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:23 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/19 13:35:59 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_table *table)
{
	int	i;

	if (pthread_mutex_destroy(&table->print_lock) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	if (pthread_mutex_destroy(&table->table_ready) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	if (pthread_mutex_destroy(&table->stop_simlation) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	if (pthread_mutex_destroy(&table->stop_simlation_two) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	if (pthread_mutex_destroy(&table->stop_mutex) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	if (pthread_mutex_destroy(&table->chang_time) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	if (pthread_mutex_destroy(&table->check_dead) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	if (pthread_mutex_destroy(&table->inc_meals) != 0)
		return (ft_print("Failed to destroy mutex\n"));
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_mutex_destroy(&table->forks[i]) != 0)
			return (ft_print("Failed to destroy mutex\n"));
		i++;
	}
}

void	*handle_one_philo(void *tab)
{
	t_table	*table;

	table = (t_table *)tab;
	table->start_time = get_time();
	pthread_mutex_lock(&table->forks[table->philos->fork_id_left]);
	printf("%u %d %s\n", get_time() - table->start_time, table->philos[0].id,
		"has taken a fork");
	ft_usleep(table->time_to_die, table->philos);
	pthread_mutex_unlock(&table->forks[table->philos->fork_id_left]);
	pthread_mutex_lock(&table->print_lock);
	printf("%u %d %s\n", get_time() - table->start_time, table->philos[0].id,
		"died");
	pthread_mutex_unlock(&table->print_lock);
	return (NULL);
}

void	cheak_one_philo(t_table *table)
{
	pthread_create(&table->philos[0].thread, NULL, handle_one_philo, table);
	pthread_join(table->philos[0].thread, NULL);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 6 || ac == 5)
	{
		if (parsing_data(&table, ac, av) == 1)
			return (0);
		data_init(&table);
		if (ft_atoi(av[1]) == 1)
			cheak_one_philo(&table);
		else
			start_simulation(&table);
	}
	else
	{
		printf_error("Error: Wrong number of arguments !");
		return (0);
	}
	ft_destroy_mutex(&table);
	ft_free(&table);
	return (0);
}
