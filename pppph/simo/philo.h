/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:42:32 by bouhammo          #+#    #+#             */
/*   Updated: 2024/07/23 14:29:55 by bouhammo         ###   ########.fr       */
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
	pthread_mutex_t time_mutex;
	
	unsigned int time;
	
} t_philo;

struct s_table
{
	t_philo *philos;
	int num_philo;
	unsigned int  time_to_die;
	unsigned int   time_to_eat;
	unsigned int  time_to_sleep;
	int 	meals_required;
	long  	simulation_running;
	bool 	philo_is_die;
	bool 	ready;
	pthread_mutex_t *forks;
	pthread_mutex_t print_lock;
	pthread_mutex_t table_ready;
	pthread_mutex_t print_is_die;
	pthread_mutex_t stop_mutex;
	pthread_mutex_t incr;
	pthread_mutex_t inct_meals_eaten;
	unsigned int start_time;
	int a;
	// unsigned int time;
};

long long int  	ft_atoi(const char *str);
void			parsing_data(t_table *table , int ac , char **av);
void			printf_error(char 	*str);
void 			*save_memory(size_t size);
void			data_init( t_table  *table);
// void 			printf(t_table *table);
unsigned int 	get_time();
void			start_simulation(t_table *table);
void			*philo_life_cycle(void *philo);
// void			print_status(t_philo *philo , char *status , int id_fork);
void 			eating(t_philo *philo);
void			sleeping( t_philo *philo);
void			thinking(t_philo *philo);
void			ft_usleep(unsigned int time);
void			print_output( t_philo *philo, char *status);
void print_is_die(t_table *s_table);


#endif