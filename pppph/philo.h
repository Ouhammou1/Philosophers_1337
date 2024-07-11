/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:42:32 by bouhammo          #+#    #+#             */
/*   Updated: 2024/07/11 22:39:25 by bouhammo         ###   ########.fr       */
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

#define RESET       "\033[0m"
#define RED         "\033[0;31m"
#define GREEN       "\033[0;32m"
#define YELLOW      "\033[0;33m"
#define BLUE        "\033[0;34m"
#define MAGENTA     "\033[0;35m"
#define CYAN        "\033[0;36m"
#define WHITE       "\033[0;37m" 


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