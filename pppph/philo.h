/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:42:32 by bouhammo          #+#    #+#             */
/*   Updated: 2024/07/09 19:24:44 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_table t_table;

typedef struct s_philo
{
	int id;
	int meals_eaten;
	long last_meal_time;
	pthread_t thread;
	t_table *table;
	int fork_id_left;
	int fork_id_right;
} t_philo;

struct s_table
{
	t_philo *philos;
	int num_philo;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int meals_required;
	pthread_mutex_t *forks;
	// pthread_mutex_t print_lock;
};

long  long int    ft_atoi(const char *str);
void			parsing_data(t_table *table ,char **av);
void			printf_error(char 	*str);
void 			*save_memory(size_t size);
void			data_init( t_table  *table);
void 			printffff(t_table *table);

#endif