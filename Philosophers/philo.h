/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:42:32 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/18 12:36:47 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	pthread_t			thread;
	int					fork_id_left;
	int					fork_id_right;
	t_table				*table;
}						t_philo;

struct					s_table
{
	t_philo				*philos;
	int					num_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					meals_required;
	long				simulation_running;
	bool				philo_is_die;
	bool				ready;
	unsigned int		start_time;

	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		table_ready;
	pthread_mutex_t		stop_simlation;
	pthread_mutex_t		stop_simlation_two;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		chang_time;
	pthread_mutex_t		check_dead;
	pthread_mutex_t		inc_meals;
	long				stop;
};

void					*philo_life_cycle(void *data);
void					thinking(t_philo *philo);
void					sleeping(t_philo *philo);
void					eating(t_philo *philo);
void					start_simulation(t_table *table);
void					monitor_simulation(t_table *table);
void					check_meals_required(t_table *table);
void					start_simulation_threads(t_table *table);
int						philo_is_died(t_table *table);

void					data_init(t_table *table);
void					init_table(t_table *table);
int						parsing_data(t_table *table, int ac, char **av);
int						ft_isdigit(int c);

void					print_output(t_philo *philo, char *status);
void					ft_usleep(unsigned int time, t_philo *philo);
unsigned int			get_time(void);
void					*save_memory(size_t size);
void					printf_error(char *str);

long long int			ft_atoi(const char *str);

void					change_boolian(pthread_mutex_t *mutex, bool *dest,
							bool value);
void					setting_variables(pthread_mutex_t *mutex, long *dest,
							long value);
void					increment(pthread_mutex_t *mutex, int *val);
long					get_long(pthread_mutex_t *mutex, long *value);
bool					read_variables(pthread_mutex_t *mutex, bool *value);

void					ft_free(t_table *table);
void					ft_print(char *ptr);
void					ft_destroy_mutex(t_table *table);
void					*handle_one_philo(void *tab);
int						check_is_valid(int ac, char **av);
void					cheak_one_philo(t_table *table);

#endif