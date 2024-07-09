
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philosopher {
    int id;
    int meals_eaten;
    long last_meal_time;
    pthread_t thread;
    struct s_table *table;
} t_philosopher;

typedef struct s_table {
    int num_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int meals_required;
    pthread_mutex_t *forks;
    t_philosopher *philosophers;
    pthread_mutex_t print_lock;
} t_table;

long get_current_time_in_ms();
void *philosopher_lifecycle(void *arg);
void init_philosophers(t_table *table);
void destroy_philosophers(t_table *table);
void monitor_philosophers(t_table *table);



long get_current_time_in_ms() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void print_state(t_table *table, int id, const char *state) {
    pthread_mutex_lock(&table->print_lock);
    printf("%ld %d %s\n", get_current_time_in_ms(), id, state);
    pthread_mutex_unlock(&table->print_lock);
}

void *philosopher_lifecycle(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    t_table *table = philo->table;

    while (1) {
        // Thinking
        print_state(table, philo->id, "is thinking");

        // Taking forks
        pthread_mutex_lock(&table->forks[philo->id]);
        print_state(table, philo->id, "has taken a fork");
        pthread_mutex_lock(&table->forks[(philo->id + 1) % table->num_philosophers]);
        print_state(table, philo->id, "has taken a fork");

        // Eating
        print_state(table, philo->id, "is eating");
        philo->last_meal_time = get_current_time_in_ms();
        usleep(table->time_to_eat * 1000);
        philo->meals_eaten++;

        // Releasing forks
        pthread_mutex_unlock(&table->forks[philo->id]);
        pthread_mutex_unlock(&table->forks[(philo->id + 1) % table->num_philosophers]);

        // Sleeping
        print_state(table, philo->id, "is sleeping");
        usleep(table->time_to_sleep * 1000);
    }

    return NULL;
}

void init_philosophers(t_table *table) {
    for (int i = 0; i < table->num_philosophers; i++) {
        table->philosophers[i].id = i;
        table->philosophers[i].meals_eaten = 0;
        table->philosophers[i].last_meal_time = get_current_time_in_ms();
        table->philosophers[i].table = table;
        pthread_create(&table->philosophers[i].thread, NULL, philosopher_lifecycle, &table->philosophers[i]);
    }
}

void destroy_philosophers(t_table *table) {
    for (int i = 0; i < table->num_philosophers; i++) {
        pthread_join(table->philosophers[i].thread, NULL);
    }
}

void monitor_philosophers(t_table *table) {
    while (1) {
        for (int i = 0; i < table->num_philosophers; i++) {
            if (get_current_time_in_ms() - table->philosophers[i].last_meal_time > table->time_to_die) {
                print_state(table, table->philosophers[i].id, "died");
                exit(0);
            }
        }
        usleep(1000);
    }
}

int main(int argc, char **argv) {
    if (argc < 5 || argc > 6) {
        printf("Usage: %s num_philosophers time_to_die time_to_eat time_to_sleep [meals_required]\n", argv[0]);
        return 1;
    }

    t_table table;
    table.num_philosophers = atoi(argv[1]);
    table.time_to_die = atol(argv[2]);
    table.time_to_eat = atol(argv[3]);
    table.time_to_sleep = atol(argv[4]);
    table.meals_required = (argc == 6) ? atoi(argv[5]) : -1;

    table.philosophers = malloc(table.num_philosophers * sizeof(t_philosopher));
    table.forks = malloc(table.num_philosophers * sizeof(pthread_mutex_t));
    pthread_mutex_init(&table.print_lock, NULL);

    for (int i = 0; i < table.num_philosophers; i++) {
        pthread_mutex_init(&table.forks[i], NULL);
    }

    init_philosophers(&table);
    monitor_philosophers(&table);
    destroy_philosophers(&table);

    for (int i = 0; i < table.num_philosophers; i++) {
        pthread_mutex_destroy(&table.forks[i]);
    }
    free(table.philosophers);
    free(table.forks);
    pthread_mutex_destroy(&table.print_lock);

    return 0;
}
