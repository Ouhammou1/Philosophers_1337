/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:15 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/18 11:51:30 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->fork_id_left]);
	pthread_mutex_lock(&philo->table->forks[philo->fork_id_right]);
	print_output(philo, "has taken a fork");
	print_output(philo, "has taken a fork");
	print_output(philo, "is eating");
	ft_usleep(philo->table->time_to_eat, philo);
	pthread_mutex_lock(&philo->table->chang_time);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->table->chang_time);
	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_right]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_left]);
	pthread_mutex_lock(&philo->table->inc_meals);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->inc_meals);
}

void	sleeping(t_philo *philo)
{
	print_output(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	print_output(philo, "is thinking");
}

long long int	ft_atoi(const char *str)
{
	int						i;
	int						s;
	unsigned long long int	r;

	i = 0;
	s = 1;
	r = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = s * (-1);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		r = (r * 10) + (str[i] - 48);
		if (s == 1 && r > 9223372036854775807)
			return (-1);
		if (s == (-1) && r > 9223372036854775807)
			return (0);
		i++;
	}
	return (r * s);
}
