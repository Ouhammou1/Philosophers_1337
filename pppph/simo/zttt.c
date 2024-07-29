

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