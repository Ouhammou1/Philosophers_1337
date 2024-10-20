/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_functons_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:32:50 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/18 12:35:44 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_table *table)
{
	free(table->philos);
	table->philos = NULL;
	free(table->forks);
	table->forks = NULL;
	return ;
}

void	ft_print(char *ptr)
{
	printf("%s", ptr);
	return ;
}

int	philo_is_died(t_table *table)
{
	pthread_mutex_lock(&table->table_ready);
	if (table->stop == 1)
	{
		pthread_mutex_unlock(&table->table_ready);
		return (1);
	}
	pthread_mutex_unlock(&table->table_ready);
	return (0);
}
