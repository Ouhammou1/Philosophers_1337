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
    unsigned int time;
} t_philo;

struct s_table
{
    t_philo *philos;
    int num_philo;
    unsigned int time_to_die;
    unsigned int time_to_eat;
    unsigned int time_to_sleep;
    int meals_required;
    int simulation_running;
    bool philo_is_die;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t print_is_die;
    unsigned int start_time;
    int a;
};

long long int ft_atoi(const char *str);
void parsing_data(t_table *table, int ac, char **av);
void printf_error(char *str);
void *save_memory(size_t size);
void data_init(t_table *table);
void printffff(t_table *table);
unsigned int get_time();
void start_simulation(t_table *table);
void *philo_life_cycle(void *philo);
void eating(t_philo *philo);
void sleeping(t_philo *philo);
void thinking(t_philo *philo);
void ft_usleep(unsigned int time);
void print_output(t_philo *philo, char *status, int id_fork);
void print_is_die(t_table *s_table);

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
    void *ptr = malloc(size);
    if (!ptr)
        printf_error("Malloc failed");
    return (ptr);
}

unsigned int get_time()
{
    struct timeval av;
    gettimeofday(&av, NULL);
    return ((av.tv_sec * 1000) + (av.tv_usec / 1000));
}

void ft_usleep(unsigned int time)
{
    unsigned int start = get_time();
    while ((get_time() - start) < time)
    {
        usleep(500);
    }
}

void print_output(t_philo *philo, char *status, int id_fork)
{
    if (!philo->table->a)
    {
        pthread_mutex_lock(&philo->table->print_lock);
        printf("Time %u | Philo id = %d | status : %s %d\n", get_time() - philo->table->start_time, philo->id, status, id_fork);
        pthread_mutex_unlock(&philo->table->print_lock);
    }
}

void print_is_die(t_table *table)
{
    pthread_mutex_lock(&table->print_lock);
    printf("Time %u | Philo id = %d | status : %s\n", get_time() - table->start_time, table->philos->id, "-<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>> is died");
    pthread_mutex_unlock(&table->print_lock);
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
        printf_error("Error: Wrong number of arguments !");
    return (0);
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
                printf_error("Enter Numbers Please !");
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
        table->meals_required = -1;
}

void data_init(t_table *table)
{
    int i;

    table->philos = save_memory(sizeof(t_philo) * table->num_philo);
    table->forks = save_memory(sizeof(pthread_mutex_t) * table->num_philo);
    table->simulation_running = 1;
    table->philo_is_die = false;
    table->start_time = get_time();
    if (pthread_mutex_init(&table->print_lock, NULL) != 0)
        printf_error("Mutex init of print_lock is failed");
    if (pthread_mutex_init(&table->print_is_die, NULL) != 0)
        printf_error("Mutex init of print_is_die is failed");
    i = 0;
    while (i < table->num_philo)
    {
        table->philos[i].id = i + 1;
        table->philos[i].meals_eaten = 0;
        table->philos[i].last_meal_time = get_time();
        table->philos[i].table = table;
        table->philos[i].fork_id_left = i;
        table->philos[i].fork_id_right = (i + 1) % table->num_philo;
        table->philos[i].time = 0;
        if (pthread_mutex_init(&table->forks[i], NULL) != 0)
            printf_error("Mutex init of forks[i] is failed");
        i++;
    }
}

void start_simulation(t_table *table)
{
    int i = 0;
    int k = 0;
    table->a = 0;
    int ret;
    table->simulation_running = 1;
    while (i < table->num_philo)
    {
        ft_usleep(100);
        ret = pthread_create(&table->philos[i].thread, NULL, philo_life_cycle, &table->philos[i]);
        if (ret != 0)
            printf_error("Error creating thread");
        i++;
    }
    while (table->simulation_running)
    {
        ft_usleep(100);
        if (table->meals_required != -1)
        {
            while (k < table->num_philo && table->philos[k].meals_eaten >= table->meals_required)
                k++;
            if (k == table->num_philo)
            {
                table->a = 1;
                table->simulation_running = 0;
                printf("OK\n");
                break;
            }
        }
        int j = 0;
        while (j < table->num_philo)
        {
            if (get_time() - table->philos[j].time >= table->time_to_die)
            {
                table->philo_is_die = true;
                pthread_mutex_lock(&table->print_lock);
                printf("Time %u | Philo id = %d | status : MAAAAAAAAT !!\n", get_time() - table->start_time, table->philos->id);
                pthread_mutex_unlock(&table->print_lock);
                exit(1);
            }
            j++;
        }
    }
    int l = 0;
    while (l < table->num_philo)
    {
        pthread_join(table->philos[l].thread, NULL);
        l++;
    }
}

void eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->forks[philo->fork_id_left]);
    pthread_mutex_lock(&philo->table->forks[philo->fork_id_right]);
    print_output(philo, "taking fork", philo->fork_id_left);
    print_output(philo, "taking fork", philo->fork_id_right);
    print_output(philo, "🍽️  is eating", 0);
    philo->time = get_time();
    ft_usleep(philo->table->time_to_eat);
    print_output(philo, "putting fork", philo->fork_id_left);
    print_output(philo, "putting fork", philo->fork_id_right);
    pthread_mutex_unlock(&philo->table->forks[philo->fork_id_left]);
    pthread_mutex_unlock(&philo->table->forks[philo->fork_id_right]);
    philo->meals_eaten++;
}

void sleeping(t_philo *philo)
{
    print_output(philo, "🥱  is sleeping", 0);
    ft_usleep(philo->table->time_to_sleep);
}

void thinking(t_philo *philo)
{
    print_output(philo, "🤔  is thinking", 0);
    ft_usleep(philo->table->time_to_sleep);
}

void *philo_life_cycle(void *data)
{
    t_philo *philo = (t_philo *)data;
    while (philo->table->simulation_running != 0 && philo->table->philo_is_die == false)
    {
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
    return (NULL);
}

// // #include "philo.h"


// // unsigned int  get_time()
// // {
// // 	struct timeval av;	
// // 	gettimeofday(&av  ,NULL);
// // 	return ( (av.tv_sec * 1000) + (av.tv_usec / 1000));
// // }
// //  void ft_usleep(unsigned int time)
// // {
// // 	unsigned int start = get_time();
// // 	while ((get_time() - start) < time)
// // 	{
// // 		usleep(100);
// // 	}
// // }
// // int main()
// // {
// // 	unsigned int start = get_time();
// // 	ft_usleep(120);
// // 	unsigned int end  = get_time();
// // 	unsigned int rse =  end - start  ;
// // 	printf("start = %u \n", start );
// // 	printf("end   = %u \n", end );
// // 	printf("%u time of the usleep  :  \n", rse);
// // 	return 0;
// // }

// pthread_mutex_t  mutx;

// void 	*func(void *arg)
// {
// 	int i=0;
// 	int *num;
// 	// pthread_mutex_init(&mutx  , NULL);
// 	num = arg;
// 	while (i < 10)
// 	{
// 		(*num)++;
// 		printf("num = %d \n", *num);
// 		i++;
// 	}
// 		// pthread_mutex_lock(&mutx);
// 		// pthread_mutex_unlock(&mutx);
	
// 	return NULL;
// }
// void 	*func1(void *arg)
// {
// 	int i=0;
// 	int *num;

// 	// pthread_mutex_init(&mutx  , NULL);
// 	num = arg;
// 	while (i < 10)
// 	{
// 		(*num) = (*num) + (*num);
// 		printf("num 1 = %d \n", *num);
// 		i++;
// 	}
// 		// pthread_mutex_lock(&mutx);
// 		// pthread_mutex_unlock(&mutx);
	
// 	return NULL;
// }
// int main(){
// 	pthread_t t1;
// 	pthread_t t2;

// 	int *num = (int *)malloc(sizeof(int));
// 	if(num == 0)
// 		return 0;
// 	*num = 1000;
// 	if(pthread_create(&t1, NULL, func, num))
// 		return 0;
// 	if(pthread_create(&t2, NULL , func1 , num))
// 		return 0;
	
// 	pthread_join(t1 , NULL);
// 	pthread_join(t2 , NULL);
// 	return 0;
// }




// #include <pthread.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <sys/time.h>

// typedef struct s_philo {
//     int             id;
//     int             left_fork;
//     int             right_fork;
//     long long       last_meal_time;
//     int             meals_eaten;
//     pthread_t       thread;
//     struct s_info   *info;
// } t_philo;

// typedef struct s_info {
//     int             num_philos;
//     int             time_to_die;
//     int             time_to_eat;
//     int             time_to_sleep;
//     int             num_meals;
//     int             all_alive;
//     long long       start_time;
//     pthread_mutex_t *forks;
//     pthread_mutex_t print_mutex;
//     pthread_mutex_t death_mutex;
//     t_philo         *philos;
// } t_info;

// int     init_info(t_info *info, int argc, char **argv);
// void    *philo_routine(void *philo_void);
// long long current_time(void);
// void    print_status(t_info *info, int id, char *message);
// void    clean_up(t_info *info);

