/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:42:32 by bouhammo          #+#    #+#             */
/*   Updated: 2024/07/11 21:46:10 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>


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
	int time_to_die;
	unsigned int   time_to_eat;
	unsigned int  time_to_sleep;
	int meals_required;
	pthread_mutex_t *forks;
	bool  	simulation_running;
	pthread_mutex_t print_lock;
};

long long int  	ft_atoi(const char *str);
void			parsing_data(t_table *table , int ac , char **av);
void			printf_error(char 	*str);
void 			*save_memory(size_t size);
void			data_init( t_table  *table);
void 			printffff(t_table *table);
unsigned int 	get_time();
void			start_simulation(t_table *table);
void			*philo_life_cycle(void *philo);
// void			print_status(t_philo *philo , char *status , int id_fork);
void 			eating(t_philo *philo);
#endif