#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>


typedef struct s_table t_table;

typedef struct s_fork 
{
    int fork_id;
    pthread_mutex_t fork;
} t_fork;


typedef struct s_philo 
{
	int id;
	long meals_count;
	bool full;
	long last_meal_time; 
	t_fork *left_fork;
	t_fork *right_fork;
	pthread_t thread_id;
	t_table *table;

} t_philo;

struct s_table
{
	long philo_nbr;
	long time_to_die;
	long time_to_est;
	long time_to_sleep;
	long meals_nbr;
	long start_simulation;
	bool end_simalation;
	t_fork *forks;
	t_philo *philos;
};

void 	print_eror(char *str);
void	parse_input( t_table *table ,char **av);
long  long int    ft_atoi(const char *str);
#endif