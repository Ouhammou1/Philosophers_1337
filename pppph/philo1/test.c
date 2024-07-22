// #include "philo.h"


// unsigned int  get_time()
// {
// 	struct timeval av;	
// 	gettimeofday(&av  ,NULL);
// 	return ( (av.tv_sec * 1000) + (av.tv_usec / 1000));
// }
//  void ft_usleep(unsigned int time)
// {
// 	unsigned int start = get_time();
// 	while ((get_time() - start) < time)
// 	{
// 		usleep(100);
// 	}
// }
// int main()
// {
// 	unsigned int start = get_time();
// 	ft_usleep(120);
// 	unsigned int end  = get_time();
// 	unsigned int rse =  end - start  ;
// 	printf("start = %u \n", start );
// 	printf("end   = %u \n", end );
// 	printf("%u time of the usleep  :  \n", rse);
// 	return 0;
// }

pthread_mutex_t  mutx;

void 	*func(void *arg)
{
	int i=0;
	int *num;
	// pthread_mutex_init(&mutx  , NULL);
	num = arg;
	while (i < 10)
	{
		(*num)++;
		printf("num = %d \n", *num);
		i++;
	}
		// pthread_mutex_lock(&mutx);
		// pthread_mutex_unlock(&mutx);
	
	return NULL;
}
void 	*func1(void *arg)
{
	int i=0;
	int *num;

	// pthread_mutex_init(&mutx  , NULL);
	num = arg;
	while (i < 10)
	{
		(*num) = (*num) + (*num);
		printf("num 1 = %d \n", *num);
		i++;
	}
		// pthread_mutex_lock(&mutx);
		// pthread_mutex_unlock(&mutx);
	
	return NULL;
}
int main(){
	pthread_t t1;
	pthread_t t2;

	int *num = (int *)malloc(sizeof(int));
	if(num == 0)
		return 0;
	*num = 1000;
	if(pthread_create(&t1, NULL, func, num))
		return 0;
	if(pthread_create(&t2, NULL , func1 , num))
		return 0;
	
	pthread_join(t1 , NULL);
	pthread_join(t2 , NULL);
	return 0;
}




#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo {
    int             id;
    int             left_fork;
    int             right_fork;
    long long       last_meal_time;
    int             meals_eaten;
    pthread_t       thread;
    struct s_info   *info;
} t_philo;

typedef struct s_info {
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             num_meals;
    int             all_alive;
    long long       start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    t_philo         *philos;
} t_info;

int     init_info(t_info *info, int argc, char **argv);
void    *philo_routine(void *philo_void);
long long current_time(void);
void    print_status(t_info *info, int id, char *message);
void    clean_up(t_info *info);

