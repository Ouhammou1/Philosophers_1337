
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };

sem_t mutex;
sem_t S[N];

void test(int phnum)
{
    if (state[phnum] == HUNGRY
        && state[LEFT] != EATING
        && state[RIGHT] != EATING) {
        // state that eating
        state[phnum] = EATING;

        sleep(2);

        printf("Philosopher %d takes fork %d and %d\n",
                      phnum + 1, LEFT + 1, phnum + 1);

        printf("Philosopher %d is Eating\n", phnum + 1);

        // sem_post(&S[phnum]) has no effect
        // during takefork
        // used to wake up hungry philosophers
        // during putfork
        sem_post(&S[phnum]);
    }
}

// take up chopsticks
void take_fork(int phnum)
{

    sem_wait(&mutex);

    // state that hungry
    state[phnum] = HUNGRY;

    printf("Philosopher %d is Hungry\n", phnum + 1);

    // eat if neighbours are not eating
    test(phnum);

    sem_post(&mutex);

    // if unable to eat wait to be signalled
    sem_wait(&S[phnum]);

    sleep(1);
}

// put down chopsticks
void put_fork(int phnum)
{

    sem_wait(&mutex);

    // state that thinking
    state[phnum] = THINKING;

    printf("Philosopher %d putting fork %d and %d down\n",
           phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);

    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);
}

void* philosopher(void* num)
{

    while (1) {

        int* i = num;

        sleep(1);

        take_fork(*i);

        sleep(0);

        put_fork(*i);
    }
}

int main()
{

    int i;
    pthread_t thread_id[N];

    // initialize the semaphores
    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++)

        sem_init(&S[i], 0, 0);

    for (i = 0; i < N; i++) {

        // create philosopher processes
        pthread_create(&thread_id[i], NULL,
                       philosopher, &phil[i]);

        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < N; i++)

        pthread_join(thread_id[i], NULL);
}




// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/time.h>


// typedef struct s_table t_table;

// typedef struct s_philo
// {
// 	int id;
// 	int meals_eaten;
// 	long last_meal_time;
// 	pthread_t thread;
// 	t_table *table;
// 	int fork_id_left;
// 	int fork_id_right;
// } t_philo;

// struct s_table
// {
// 	t_philo *philos;
// 	int num_philo;
// 	long time_to_die;
// 	long time_to_eat;
// 	long time_to_sleep;
// 	int meals_required;
// 	pthread_mutex_t *forks;
// 	// pthread_mutex_t print_lock;
// };

// long  long int    ft_atoi(const char *str);
// void			parsing_data(t_table *table , int ac , char **av);
// void			printf_error(char 	*str);
// void 			*save_memory(size_t size);
// void			data_init( t_table  *table);
// void 			printffff(t_table *table);




// long  long int    ft_atoi(const char *str)
// {
//         int                                             i;
//         int                                             s;
//         unsigned long long int  r;

//         i = 0;
//         s = 1;
//         r = 0;
//         while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
//                 i++;
//         if (str[i] == '-' || str[i] == '+')
//         {
//                 if (str[i] == '-')
//                         s = s * (-1);
//                 i++;
//         }
//         while (str[i] >= 48 && str[i] <= 57)
//         {
//                 r = (r * 10) + (str[i] - 48);
//                 if (s == 1 && r > 9223372036854775807)
//                         return (-1);
//                 if (s == (-1) && r > 9223372036854775807)
//                         return (0);
//                 i++;
//         }
//         return (r * s);
// }


// void	printf_error(char 	*str)
// {
// 	printf("%s\n", str);
// 	exit(1);
// }

// void 	*save_memory(size_t size)
// {
// 	void *ptr;

// 	ptr = malloc(size);
// 	if(!ptr)
// 		printf_error("Malloc failed");
// 	return (ptr);
// }
// int main(int ac , char **av)
// {
// 	t_table table;

// 	if(ac == 6 || ac == 5)
// 	{
// 		parsing_data(&table , ac, av);
// 		data_init(&table);
// 	}
// 	else
// 		printf_error("Error: Wrong number of arguments\n");

// 	return (0);
// }

// int	ft_isdigit(int c)

// {
// 	if (c >= 48 && c <= 57)
// 	{
// 		return (1);
// 	}
// 	return (0);
// }

// void	parsing_data(t_table *table , int  ac , char **av)
// {
// 	int  i=1;
// 	while (i < ac )
// 	{
// 		int j =0;
// 		while (av[i][j] != '\0')
// 		{
// 			printf("%c    ->>>>> \n",av[i][j]);
// 			if( ft_isdigit(av[i][j]) == 0)
// 				printf_error("Enter Numbers Please !\n");
// 			j++;
// 		}
// 		i++;
// 	}
// 	table->num_philo = ft_atoi(av[1]);
// 	table->time_to_die = ft_atoi(av[2]);
// 	table->time_to_eat = ft_atoi(av[3]);
// 	table->time_to_sleep = ft_atoi(av[4]);
// 	if (av[5])
// 		table->meals_required = ft_atoi(av[5]);
// 	else
// 		table->meals_required = 0;
// }

// void		data_init( t_table  *table)
// {
// 	int i;

// 	table->philos = save_memory(sizeof(t_philo) * table->num_philo);
// 	table->forks = save_memory(sizeof(pthread_mutex_t) * table->num_philo);

// 	i = 0;
// 	while (i < table->num_philo)
// 	{
// 		table->philos[i].id = i ;
// 		table->philos[i].meals_eaten = 0;
// 		table->philos[i].last_meal_time = 0;
// 		table->philos[i].table = table;
// 		table->philos[i].fork_id_left= i;
// 		table->philos[i].fork_id_right = (i + 1) % table->num_philo;
// 		if ( pthread_mutex_init(&table->forks[i], NULL) !=0)
// 			printf_error("Mutex init  of forks[i] is failed");	

// 		i++;
// 	}
// 		printffff(table);
// }

// void 	printffff(t_table *table)
// {
// 	int i =0;
// 	printf("table num_philo = %d \n", table->num_philo);
// 	printf("table time to die = %ld\n", table->time_to_die);
// 	printf("table time to est  = %ld\n", table->time_to_eat);
// 	printf("table time to sleep = %ld\n", table->time_to_sleep);
// 	printf("table meals reauired  = %d\n",  table->meals_required);
// 	printf("table philo = %p \n\n", table->philos);

// 	while (i  < table->num_philo)
// 	{
// 		printf("		philo id = %d \n", table->philos[i].id);
// 		printf("		philo meals_eaten = %d \n", table->philos[i].meals_eaten);
// 		printf("		philo last_meal_time = %ld \n", table->philos[i].last_meal_time);
// 		printf("		philo table = %p \n", table->philos[i].table);
// 		printf("		philo fork id left = %d \n", table->philos[i].fork_id_left);
// 		printf("		philo fork id right = %d \n", table->philos[i].fork_id_right);
// 		printf("		addres of mutex fork = %d || %p \n\n" , i , &table->forks[i]);
// 		i++;
// 	}
// }



// /*********************************************************************************************/

// void Philosopher  
// {  
//  while(1)  
//   {  
//   take_fork[i];  
//   take_fork[ (i+1) % 5] ;  
    
//   EATING THE NOODLE  
    
//   put_fork[i];  
//   put_fork[ (i+1) % 5] ;  
    
//    THINKING  
//   }  
// }  




