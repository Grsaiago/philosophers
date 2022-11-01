#include "philosophers_bonus.h"

void	*ph_calloc(int size, int bytes)
{
	void	*ptr;

	if (size <= 0 || bytes <= 0)
		return (NULL);
	ptr = malloc(size * bytes);
	if (!ptr)
		return (NULL);
	ptr = memset(ptr, 0, (size * bytes) - 1);
	if (!ptr)
		return (NULL);
	return (ptr);
}

long int	get_time(struct timeval *tv, int i)
{
	long int	current_time;

	gettimeofday(tv, NULL);
	current_time = ((tv->tv_sec * 1000000) + tv->tv_usec);
	return (current_time / i);
}

void	*vulture_exec(void *ptr)
{
	t_control	*control;
	long int	diff;
	long int	current_time;

	control = (t_control *)ptr;
	current_time = get_time(&control->tv, 1);
	pthread_mutex_lock(&control->last_meal_access);
	diff = current_time - control->last_meal;
	if (diff > control->time_to_die && (control->last_meal != 0))
	{
		current_time = get_time(&control->tv, 100);
		pthread_mutex_unlock(&control->last_meal_access);
		printf("%ld %d has died\n", current_time, control->phid);
		sem_post(control->death_sem);
	}
	pthread_mutex_unlock(&control->last_meal_access);
	sem_post(control->death_sem);
	return (NULL);
}

void	death_refresh(t_control *control)
{
	long unsigned int	current_time;

	pthread_mutex_lock(&control->last_meal_access);
	current_time = get_time(&control->tv, 1);
	control->last_meal = current_time;
	pthread_mutex_unlock(&control->last_meal_access);
	return ;
}
