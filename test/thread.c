#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>


int main()
{
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex , NULL);
	printf("Can you use the mutex from now on \n");
	pthread_mutex_destroy(&mutex);
	return 0;
}
// #include <string.h>
// void *thread(void *arg) {
//   char *ret;
//   printf("thread() entered with argument '%s'\n", arg);
//   if ((ret = (char*) malloc(20)) == NULL) {
//     perror("malloc() error");
//     exit(2);
//   }
//   strcpy(ret, "This is a test");
//   pthread_exit(ret);
// }

// int  main() {
//   pthread_t thid;
//   void *ret;

//   if (pthread_create(&thid, NULL, thread, "thread 1") != 0) {
//     perror("pthread_create() error");
//     exit(1);
//   }

//   if (pthread_join(thid, &ret) != 0) {
//     perror("pthread_create() error");
//     exit(3);
//   }

//   printf("thread exited with '%s'\n", ret);
// }


// int main()
// {
//     pthread_mutexattr_t attr ;
//     pthread_mutex_t mutex ;


//     pthread_mutexattr_init(&attr);

//     pthread_mutexattr_settype(&attr  , PTHREAD_MUTEX_RECURSIVE);;

//     int ret = pthread_mutex_init(&mutex, &attr);
//     if(ret != 0)
//     {
//         printf("pppppppppp\n");
//         return 0;
//     }

//     pthread_mutexattr_destroy(&attr);


//     pthread_mutex_lock(&mutex);
//     pthread_mutex_unlock(&mutex);

//     // Destruction du mutex après utilisation
//     pthread_mutex_destroy(&mutex);

//     // int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);

//}

// int main()
// {
//     struct timeval av;
//     gettimeofday(&av ,NULL);

//     printf("Seconde est %ld \n" , av.tv_sec);
//     printf("MuliSeconde est %d \n" , av.tv_usec);

// }


// int glb = 0;
// pthread_mutex_t lock;

// void* routine()
// {
//     for (int i = 0; i < 58456156; i++)
//     {
//         pthread_mutex_lock(&lock);
//         glb++;
//         pthread_mutex_unlock(&lock);
//     }
//     return NULL;
// }

// int main(int ac, char **av)
// {
//     pthread_t p1, p2;

//     pthread_mutex_init(&lock, NULL);

//     if (pthread_create(&p1, NULL, routine, NULL) != 0)
//         return 1;
//     if (pthread_create(&p2, NULL, routine, NULL) != 0)
//         return 2;
//     if (pthread_join(p1, NULL) != 0)
//         return 3;
//     if (pthread_join(p2, NULL) != 0)
//         return 4;


//     printf("glb = %d\n", glb);

//     pthread_mutex_destroy(&lock);

//     return 0;
// }



// void* thread_function(void* arg) {
//     printf("Thread détaché en cours d'exécution\n");
//     sleep(2); // Simuler un travail du thread
//     printf("Thread détaché terminé 4444444\n");
//     return NULL;
// }

// int main() {
//     pthread_t thread;
//     int result;

//     // Créer un nouveau thread
//     result = pthread_create(&thread, NULL, thread_function, NULL);
//     if (result != 0) {
//         perror("Erreur lors de la création du thread");
//         exit(EXIT_FAILURE);
//     }

//     // Détacher le thread
//     result = pthread_join(thread , NULL);
//     if (result != 0) {
//         perror("Erreur lors du détachement du thread");
//         exit(EXIT_FAILURE);
//     }

//     // Thread principal fait d'autres choses
//     printf("Thread principal en cours d'exécution\n");
//     // sleep(3); // Attendre pour s'assurer que le thread détaché se termine
//     printf("Thread principal terminé\n");
//     return 0;
// }



// void 	*thread_function(void	 *arg)
// {
// 	printf("Thread en cours d'execution \n");
// 	return NULL;

// }

// int main()
// {
// 	pthread_t thread;
// 	int result ;

// 	result = pthread_create(&thread , NULL, thread_function , NULL);
// 	result = pthread_detach(thread);
// 	pthread_join(thread , NULL);

// 	printf("////////Thread principal en cours dexecution \n");

// 	return 0;
// }


// int main()
// {
// 	struct timeval va; 

// 	int t = gettimeofday(&va , NULL);
// 	if ( t == 0)
// 	{
// 		printf("Secods is %ld \n", va.tv_sec );
// 		printf("Mecroseconds   is %d \n" , va.tv_usec);
// 	}
// }

// void 	*func( void *arg)
// {
// 	printf("Bonjour a touts\n");
// 	pthread_exit(0);
// }


// int main()
// {
// 	pthread_t thread[4];

// 	int i=0;
// 	while (i < 4)
// 	{
// 		pthread_create(&thread[i] , NULL , func , NULL);
// 		i++;
// 	}

// 	i =2;
// 	while ( i < 4)
// 	{
// 		// pthread_join(thread[i] , NULL);
// 		i++;
// 	}
	
	
// }

// int n1, n2;
// void    *hello(void *arg)
// {
//     int sum = n1 + n2;
// 	printf("La somme est %d \n", sum);
//     pthread_exit(0);
// }

// int main()
// {
//     pthread_t thread;
// 	printf("Entrez la valeur de  n1 et n2 \n");
// 	scanf("%d",&n1);
// 	scanf("%d",&n2);

//     pthread_create(&thread , NULL , hello ,NULL);
//     pthread_join(thread , NULL);
//     return 0;
// }









// void *threadfunction( void *arg)
// {
//     // int k = (int) arg;
//     printf("arg = %d\n", *(int*)arg);

//     pthread_exit(NULL);
// }

// int main ()
// {
//     pthread_t thread;
//     void *retval ;
//     int o = 852;

//     int rc = pthread_create(&thread , NULL, threadfunction, &o);
//     if(rc )
//     {
//         printf("ERROR ; return from pthread_create() is %d \n", rc);
//         exit(-1);
//     }

//     rc = pthread_join(thread , &retval);
//     if(rc )
//     {
//         printf("ERROR ; return from pthread_create() is %d \n", rc);
//         exit(-1);
//     }

// }




// // Structure pour passer les paramètres au thread
// typedef struct {
//     int *array;
//     int start;
//     int end;
//     long sum;
// } thread_data_t;

// // Fonction exécutée par chaque thread pour calculer la somme partielle
// void *sumArray(void *threadarg) {
//     thread_data_t *data = (thread_data_t *)threadarg;
//     data->sum = 0;
//     for (int i = data->start; i < data->end; i++) {
//         data->sum += data->array[i];
//     }
//     pthread_exit(NULL);
// }

// int main() {
//     const int ARRAY_SIZE = 100;
//     const int NUM_THREADS = 4;
//     int array[ARRAY_SIZE];
//     pthread_t threads[NUM_THREADS];
//     thread_data_t thread_data[NUM_THREADS];
//     int segment_size = ARRAY_SIZE / NUM_THREADS;
//     long total_sum = 0;

//     // Initialiser le tableau avec des valeurs aléatoires
//     for (int i = 0; i < ARRAY_SIZE; i++) {
//         array[i] = rand() % 100; // Valeurs aléatoires entre 0 et 99
//     }

//     // Créer les threads pour calculer les sommes partielles
//     for (int i = 0; i < NUM_THREADS; i++) {
//         thread_data[i].array = array;
//         thread_data[i].start = i * segment_size;
//         if (i == NUM_THREADS - 1) {
//             thread_data[i].end = ARRAY_SIZE;
//         } else {
//             thread_data[i].end = (i + 1) * segment_size;
//         }
//         thread_data[i].sum = 0;
        
//         int rc = pthread_create(&threads[i], NULL, sumArray, (void *)&thread_data[i]);
//         if (rc) {
//             printf("ERROR; return code from pthread_create() is %d\n", rc);
//             exit(-1);
//         }
//     }

//     // Attendre que tous les threads se terminent et récupérer les sommes partielles
//     for (int i = 0; i < NUM_THREADS; i++) {
//         pthread_join(threads[i], NULL);
//         total_sum += thread_data[i].sum;
//     }

//     printf("Total sum: %ld\n", total_sum);

//     return 0;
// }
