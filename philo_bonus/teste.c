#include "philosophers_bonus.h"

int	main(void)
{
	int	i;
	int	*philov;
	int	id;
	t_control *control;	

	control = &(t_control){0};
	control->nph = 3;
	control->philov = (int *)ph_calloc(sizeof(int), control->nph + 1);
	control->forks = sem_open("forks", O_CREAT, O_RDWR, control->nph);
	control->death_sem = sem_open("death", O_CREAT, O_RDWR, 0);
	control->time_to_eat = 200;
	control->time_to_die = 1000;
	control->time_to_sleep = 100;
	i = -1;
	while (++i < control->nph)
	{
	    control->philov[i] = fork();
		id = control->philov[i];
	    if (id == 0)
		{
			control->phid = i + 1;
		    break ;
		}
	}
	if (id == 0)
	{
		pthread_create(&control->vulture_thread, NULL, &vulture_exec, control); 
		pthread_detach(control->vulture_thread);
		while (42)
		{
			death_refresh(control);
			printf("ms %d is thinking\n", control->phid);
			sem_wait(control->forks);
			printf("ms %d has taken a fork\n", control->phid);
			sem_wait(control->forks);
			death_refresh(control);
			printf("ms %d is eating\n", control->phid);
			usleep(control->time_to_eat);
			sem_post(control->forks);
			sem_post(control->forks);
			printf("ms %d is sleeping\n", control->phid);
			usleep(control->time_to_sleep);
		}
	}
	else
	{
	    i = 0;
	    while (i < control->nph)
		{
			waitpid(control->philov[i], NULL, 0);
			i++;
		}
	}
	sem_wait(control->forks);
	i = 0;
	while (i < control->nph)
	{
		kill(control->philov[i], SIGKILL);
		i++;
	}
	free(control->philov);
	sem_close(control->forks);
	sem_close(control->death_sem);
	sem_unlink("forks");
	sem_unlink("death");
   	printf("Main Process has returned\n");
	return (0);
}
