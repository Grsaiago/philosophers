#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	int			i;
	int			*philov;
	int			pid;
	int			sem;
	t_control	*control;	

	control = &(t_control){0};
	if (validate_args(argc, argv))
		return (0);
	create_control(control, argv);
	i = -1;
	while (++i < control->nph)
	{
	    pid = fork();
	    if (pid == 0)
		{
			control->phid = i + 1;
		    break ;
		}
		else
		{
			if (!control->philov)
			{
				control->philov = (int *)ph_calloc(sizeof(int), control->nph + 1);
				control->philov[i] = pid;
			}
			else
				control->philov[i] = pid;
		}
	}
	if (pid == 0)
	{
		vulture_create(control);
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
		sem_getvalue(control->death_sem, &sem);
		printf("Valor do death_sem > %d\n", sem);
	}
	sem_wait(control->death_sem); //esse sem_wait não tá esperando, mesmo sendo inicializado com 0 na initialize control
	i = 0;
	while (i < control->nph)
	{
		kill(control->philov[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i < control->nph)
	{
		waitpid(control->philov[i], NULL, 0);
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
