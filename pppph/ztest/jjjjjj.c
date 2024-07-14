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
    pthread_mutex_t print_lock;
    int simulation_running;
};

// Function prototypes
long long int ft_atoi(const char *str);
void parsing_data(t_table *table, int ac, char **av);
void printf_error(char *str);
void *save_memory(size_t size);
void data_init(t_table *table);
void printffff(t_table *table);
long get_timestamp();
void *philosopher_lifecycle(void *arg);
void start_simulation(t_table *table);
void monitor_philosophers(t_table *table);

long long int ft_atoi(const char *str)
{
    int i = 0;
    int s = 1;
    unsigned long long int r = 0;

    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            s = s * (-1);
        i++;
    }
    while (str[i] >= 48 && str[i] <= 57)
    {
        r = (r * 10) + (str[i] - 48);
        if (s == 1 && r > 9223372036854775807)
            return (-1);
        if (s == (-1) && r > 9223372036854775807)
            return (0);
        i++;
    }
    return (r * s);
}

void printf_error(char *str)
{
    printf("%s\n", str);
    exit(1);
}

void *save_memory(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
        printf_error("Malloc failed");
    return (ptr);
}

int ft_isdigit(int c)
{
    if (c >= 48 && c <= 57)
    {
        return (1);
    }
    return (0);
}

void parsing_data(t_table *table, int ac, char **av)
{
    int i = 1;
    while (i < ac)
    {
        int j = 0;
        while (av[i][j] != '\0')
        {
            if (ft_isdigit(av[i][j]) == 0)
                printf_error("Enter Numbers Please !\n");
            j++;
        }
        i++;
    }
    table->num_philo = ft_atoi(av[1]);
    table->time_to_die = ft_atoi(av[2]);
    table->time_to_eat = ft_atoi(av[3]);
    table->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        table->meals_required = ft_atoi(av[5]);
    else
        table->meals_required = 0;
}

void data_init(t_table *table)
{
    int i;

    table->philos = save_memory(sizeof(t_philo) * table->num_philo);
    table->forks = save_memory(sizeof(pthread_mutex_t) * table->num_philo);
    table->simulation_running = 1;

    if (pthread_mutex_init(&table->print_lock, NULL) != 0)
        printf_error("Mutex init of print_lock failed");

    i = 0;
    while (i < table->num_philo)
    {
        table->philos[i].id = i + 1;
        table->philos[i].meals_eaten = 0;
        table->philos[i].last_meal_time = get_timestamp();
        table->philos[i].table = table;
        table->philos[i].fork_id_left = i;
        table->philos[i].fork_id_right = (i + 1) % table->num_philo;
        if (pthread_mutex_init(&table->forks[i], NULL) != 0)
            printf_error("Mutex init of forks[i] failed");

        i++;
    }
}

long get_timestamp()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void print_status(t_philo *philo, char *status)
{
    long timestamp = get_timestamp();
    pthread_mutex_lock(&philo->table->print_lock);
    if (philo->table->simulation_running)
        printf("%ld %d %s\n", timestamp, philo->id, status);
    pthread_mutex_unlock(&philo->table->print_lock);
}

void *philosopher_lifecycle(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_table *table = philo->table;

    while (table->simulation_running)
    {
        // Thinking
        print_status(philo, "is thinking");
        
        // Pick up forks
        pthread_mutex_lock(&table->forks[philo->fork_id_left]);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(&table->forks[philo->fork_id_right]);
        print_status(philo, "has taken a fork");

        // Eating
        print_status(philo, "is eating");
        philo->last_meal_time = get_timestamp();
        usleep(table->time_to_eat * 1000);
        philo->meals_eaten++;

        // Put down forks
        pthread_mutex_unlock(&table->forks[philo->fork_id_right]);
        pthread_mutex_unlock(&table->forks[philo->fork_id_left]);

        // Sleeping
        print_status(philo, "is sleeping");
        usleep(table->time_to_sleep * 1000);
    }
    return NULL;
}

void start_simulation(t_table *table)
{
    int i;

    i = 0;
    while (i < table->num_philo)
    {
        if (pthread_create(&table->philos[i].thread, NULL, philosopher_lifecycle, &table->philos[i]) != 0)
            printf_error("Failed to create thread");
        i++;
    }

    // Monitor philosophers' states
    monitor_philosophers(table);

    // Wait for all threads to finish
    i = 0;
    while (i < table->num_philo)
    {
        pthread_join(table->philos[i].thread, NULL);
        i++;
    }

    // Destroy mutexes
    i = 0;
    while (i < table->num_philo)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&table->print_lock);
}

void monitor_philosophers(t_table *table)
{
    while (table->simulation_running)
    {
        int i = 0;
        while (i < table->num_philo)
        {
            if ((get_timestamp() - table->philos[i].last_meal_time) > table->time_to_die)
            {
                print_status(&table->philos[i], "died");
                table->simulation_running = 0;
                break;
            }
            i++;
        }
        usleep(1000); // Check every 1 ms
    }
}

int main(int ac, char **av)
{
    t_table table;

    if (ac == 6 || ac == 5)
    {
        parsing_data(&table, ac, av);
        data_init(&table);
        start_simulation(&table);
    }
    else
        printf_error("Error: Wrong number of arguments\n");

    return 0;
}