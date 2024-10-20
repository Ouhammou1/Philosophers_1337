/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:02 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/18 14:41:14 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation_threads(t_table *table)
{
	int	i;

	table->stop = 0;
	table->start_time = get_time();
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_life_cycle,
				&table->philos[i]) != 0)
			printf_error("Error creating thread");
		i++;
	}
}

void	check_meals_required(t_table *table)
{
	int	counter;
	int	i;

	if (table->meals_required != -1)
	{
		counter = 0;
		i = 0;
		while (i < table->num_philo)
		{
			if (table->philos[i].meals_eaten >= table->meals_required)
				counter++;
			i++;
		}
		if (counter == table->num_philo)
		{
			setting_variables(&table->stop_simlation,
				&table->simulation_running, 0);
			setting_variables(&table->check_dead, &table->stop, 1);
		}
	}
}

void	monitor_simulation(t_table *table)
{
	int	i;

	while (table->simulation_running == 1)
	{
		i = 0;
		while (i < table->num_philo)
		{
			if (get_time()
				- table->philos[i].last_meal_time >= table->time_to_die)
			{
				setting_variables(&table->check_dead, &table->stop, 1);
				setting_variables(&table->stop_simlation_two,
					&table->simulation_running, 0);
				pthread_mutex_lock(&table->print_lock);
				printf("%u %d %s\n", get_time() - table->start_time,
					table->philos[i].id, "died");
				pthread_mutex_unlock(&table->print_lock);
				break ;
			}
			i++;
		}
		if (table->simulation_running == 0)
			return ;
		check_meals_required(table);
	}
}

void	start_simulation(t_table *table)
{
	int	i;

	start_simulation_threads(table);
	monitor_simulation(table);
	i = 0;
	while (i < table->num_philo)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

void	*philo_life_cycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	thinking(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat / 2, philo);
	while (1)
	{
		if (philo_is_died(philo->table) == 1)
			break ;
		if (get_long(&philo->table->stop_mutex,
				&philo->table->simulation_running) == 0)
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
