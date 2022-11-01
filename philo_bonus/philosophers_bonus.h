
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>

typedef struct s_control
{
    int					nph;
	int					phid;
    int					time_to_eat;
    int					time_to_sleep;
    int					time_to_die;
    int					max_eat;
	int					*philov;
	sem_t				*forks;
	sem_t				*death_sem;
	pthread_t			vulture_thread;
	pthread_mutex_t		last_meal_access;
	long unsigned int	last_meal;
	struct timeval	tv;

}	t_control;

void		*ph_calloc(int size, int bytes);
long int	get_time(struct timeval *tv, int i);
void		death_refresh(t_control *control);
void		*vulture_exec(void *ptr);
//void		thread_execute(t_control *control); // vai chamar a vulture, vai ser a função passada no thread_create
//void		vulture(void *ptr); //essa vai ser a função que fica vendo se o philo tem que morrer
//void		allow_death(t_control *control); // vai dar free em memória alocada pelos child e incrementar um semáforo de matar geral, que vai estar em sem_wait na main;
//void		kill_process(t_control *control); // vai dar free em memória alocada na heap e incrementar o semáforo de matar geral na main;

