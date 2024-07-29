

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_fork {
    pthread_mutex_t mutex;
} t_fork;

typedef struct s_philosopher {
    int id;
    int times_eaten;
    long long last_meal;
    pthread_t thread;
    t_fork *left_fork;
    t_fork *right_fork;
    struct s_data *data;
} t_philosopher;

typedef struct s_data {
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    long long start_time;
    t_philosopher *philosophers;
    t_fork *forks;
    pthread_mutex_t print_mutex;
    int stop_simulation;
} t_data;

long long current_timestamp();
void print_state(t_data *data, int id, const char *state);
void *philosopher_life(void *arg);


long long current_timestamp() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void print_state(t_data *data, int id, const char *state) {
    pthread_mutex_lock(&data->print_mutex);
    long long timestamp = current_timestamp() - data->start_time;
    printf("%lld %d %s\n", timestamp, id + 1, state);
    pthread_mutex_unlock(&data->print_mutex);
}

void eat(t_philosopher *philosopher) {
    t_data *data = philosopher->data;

    pthread_mutex_lock(&philosopher->left_fork->mutex);
    print_state(data, philosopher->id, "has taken a fork");
    pthread_mutex_lock(&philosopher->right_fork->mutex);
    print_state(data, philosopher->id, "has taken a fork");

    philosopher->last_meal = current_timestamp();
    print_state(data, philosopher->id, "is eating");
    usleep(data->time_to_eat * 1000);
    philosopher->times_eaten++;

    pthread_mutex_unlock(&philosopher->right_fork->mutex);
    pthread_mutex_unlock(&philosopher->left_fork->mutex);
}

void *philosopher_life(void *arg) {
    t_philosopher *philosopher = (t_philosopher *)arg;
    t_data *data = philosopher->data;

    while (!data->stop_simulation) {
        print_state(data, philosopher->id, "is thinking");
        eat(philosopher);
        if (data->number_of_times_each_philosopher_must_eat != -1 &&
            philosopher->times_eaten >= data->number_of_times_each_philosopher_must_eat) {
            data->stop_simulation = 1;
            break;
        }
        print_state(data, philosopher->id, "is sleeping");
        usleep(data->time_to_sleep * 1000);
    }
    return NULL;
}

void init_philosophers(t_data *data) {
    int i;

    data->philosophers = malloc(data->number_of_philosophers * sizeof(t_philosopher));
    data->forks = malloc(data->number_of_philosophers * sizeof(t_fork));
    for (i = 0; i < data->number_of_philosophers; i++) {
        pthread_mutex_init(&data->forks[i].mutex, NULL);
    }
    for (i = 0; i < data->number_of_philosophers; i++) {
        data->philosophers[i].id = i;
        data->philosophers[i].times_eaten = 0;
        data->philosophers[i].last_meal = current_timestamp();
        data->philosophers[i].left_fork = &data->forks[i];
        data->philosophers[i].right_fork = &data->forks[(i + 1) % data->number_of_philosophers];
        data->philosophers[i].data = data;
    }
}

int main(int argc, char **argv) {
    t_data data;
    int i;

    if (argc != 5 && argc != 6) {
        fprintf(stderr, "Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }

    data.number_of_philosophers = atoi(argv[1]);
    data.time_to_die = atoi(argv[2]);
    data.time_to_eat = atoi(argv[3]);
    data.time_to_sleep = atoi(argv[4]);
    data.number_of_times_each_philosopher_must_eat = (argc == 6) ? atoi(argv[5]) : -1;
    data.stop_simulation = 0;
    data.start_time = current_timestamp();
    pthread_mutex_init(&data.print_mutex, NULL);

    init_philosophers(&data);

    for (i = 0; i < data.number_of_philosophers; i++) {
        pthread_create(&data.philosophers[i].thread, NULL, philosopher_life, &data.philosophers[i]);
    }

    while (!data.stop_simulation) {
        for (i = 0; i < data.number_of_philosophers; i++) {
            if (current_timestamp() - data.philosophers[i].last_meal > data.time_to_die) {
                print_state(&data, i, "----------------------> died");
                data.stop_simulation = 1;
                break;
            }
        }
    }

    for (i = 0; i < data.number_of_philosophers; i++) {
        pthread_join(data.philosophers[i].thread, NULL);
    }

    for (i = 0; i < data.number_of_philosophers; i++) {
        pthread_mutex_destroy(&data.forks[i].mutex);
    }
    pthread_mutex_destroy(&data.print_mutex);
    free(data.philosophers);
    free(data.forks);

    return 0;
} 







////////////////////////////////////////////////////////////////////////////////////////

#include  "philo.h"


bool get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool res;
	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

long get_long(pthread_mutex_t *mutex, long *value)
{
	long res;
	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

void increment(pthread_mutex_t *mutex, int *val)
{
	pthread_mutex_lock(mutex);
	(*val)++;
	// printf("val---------------------------------------->>>>  = %d\n",*(int *)val);
	pthread_mutex_lock(mutex);

}

void set_long(pthread_mutex_t *mutex,long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}
void set_bool(pthread_mutex_t *mutex,bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}
void 	start_simulation(t_table *table )
{
	int  i =0;
	int k =0;
	// table->a=0;
	int ret;
	table->simulation_running = 1;
	table->start_time = get_time();
	while (i <  table->num_philo)
	{
		// ft_usleep(100);
		printf("table->philos[%d].meals_eaten  == %ld\n", i , table->philos[i].last_meal_time);
		ret = pthread_create(&table->philos[i].thread, NULL , philo_life_cycle, &table->philos[i]);
		if(ret != 0)
			printf_error("Error creating thread");
		i++;
	}
	set_bool(&table->table_ready, &table->ready, true);
	while (1)
	{
		i = 0;
		while (i < table->num_philo)
		{
			if (get_time() - get_long(&table->philos[i].time_mutex ,&table->philos[i].last_meal_time) >= table->time_to_die)
			{
				set_long(&table->stop_mutex , &table->simulation_running, 0);
				print_output(&table->philos[i], "died");
				return ;
			}
			while ( k < table->num_philo && table->philos[k].meals_eaten < table->meals_required )
			{
				printf("\n\ntable->philos[%d].meals_eaten = %d \n\n", table->philos->id ,table->philos[k].meals_eaten);
				printf("\n\ntable->meals_required  = %d \n", table->meals_required );
				increment(&table->incr , &k);
			}
// k--;
			printf("k = %d \n", k);
			if( k == table->num_philo)
			{
				set_long(&table->stop_mutex, &table->simulation_running , 0);
				printf("OK\n");
				return;
			}
			i++;
		}
	}
	// while ( table->simulation_running )
	// {
	// 	// printf("meals_eaten = %d \n", table->philos->meals_eaten);
	// 	ft_usleep(100);

	// 	if(table->meals_required != -1 )
	// 	{

	// 		while ( k < table->num_philo && table->philos[k].meals_eaten < table->meals_required )
	// 		{
	// 			printf("table->philo[%d].mleals = %d \t", k ,table->philos[k].meals_eaten);
	// 			printf("meals required = %d \n", table->meals_required);
	// 			// printf("table->philo[%d].mleals = %d \n", k ,table->philos[k].meals_eaten);
	// 			k++;
	// 		}
	// 		printf("k = %d \t\t num philo = %d \n", k , table->num_philo);
	// 		if( k == table->num_philo)
	// 		{
	// 			table->a = 1;
	// 			table->simulation_running = 0;
	// 			printf("OK\n");
	// 			break;
	// 		}
	// 			printf("			YES\n\n");
	// 		if(get_time() - table->philos[k].time >=  table->time_to_die)
	// 		{
	// 			table->a = 1;
	// 			table->philo_is_die = true;
	// 			pthread_mutex_lock(&table->print_is_die);

	// 			printf(RED "Time %u "RESET" | " YELLOW "Philo id = %d" RESET " | " CYAN "status : %s" RESET , 
	// 			get_time()- table->start_time, table->philos->id, "MAAAAAAAAT !!\n");

	// 			pthread_mutex_unlock(&table->print_is_die);
	// 			// ft_usleep(100);
	// 			// exit(1);
	// 			break;
	// 		}

		
	// 	}
	// 	// int j = 0;
	// 	// while (j <  table->num_philo)
	// 	// {
	// 	// 	if(get_time() - table->philos[j].time <  table->time_to_die)
	// 	// 	{
	// 	// 		// table->a = 1;
	// 	// 		table->simulation_running = 0;
	// 	// 		table->philo_is_die = true;
	// 	// 		pthread_mutex_lock(&table->print_lock);
	// 	// 		printf(RED "Time %u "RESET" | " YELLOW "Philo id = %d" RESET " | " CYAN "status : %s" RESET ,
	// 	// 		get_time()- table->start_time, table->philos->id, "MAAAAAAAAT !!\n\n");
	// 	// 		pthread_mutex_unlock(&table->print_lock);

	// 	// 		// ft_usleep(100);
	// 	// 		exit(1);
	// 	// 	}
	// 	// 	j++;
	// 	// }
	// 	}
	// // }
	int l = 0;
	while ( l < table->num_philo)
	{
		pthread_join(table->philos[l].thread , NULL);
		l++;	
	}
}



void eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->fork_id_left]);
	print_output(philo, "has taken a fork");

	pthread_mutex_lock(&philo->table->forks[philo->fork_id_right]);
	print_output(philo, "has taken a fork");


	print_output(philo, "is eating");
	// philo->time = get_time();
	// philo->last_meal_time = get_time();
	ft_usleep(philo->table->time_to_eat);
	set_long(&philo->time_mutex, &philo->last_meal_time, get_time());

	
	increment(&philo->table->inct_meals_eaten , &philo->meals_eaten);

	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_right]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork_id_left]);
}


void	sleeping( t_philo *philo)
{
	print_output(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_output(philo, "is thinking");
	// ft_usleep(philo->table->time_to_sleep);
}

void	*philo_life_cycle(void *data)
{

	t_philo *philo = (t_philo *)data;
	while (!get_bool(&philo->table->table_ready, &philo->table->ready))
	;
	if (philo->id % 2 != 0)
		sleeping(philo);
	while (get_long(&philo->table->stop_mutex , &philo->table->simulation_running) != 0 )//&& philo->table->philo_is_die == false )
	{
		// printf("dfgh\n");
		thinking(philo);
		eating(philo);	
		sleeping(philo);
	}
	return (NULL);
}

