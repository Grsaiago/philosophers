/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:10:10 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/03 17:48:46 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	death_refresh(t_control *control)
{
	long unsigned int	current_time;

	pthread_mutex_lock(&control->last_meal_access);
	current_time = get_time(&control->tv_last_meal, 1);
	control->last_meal = current_time;
	pthread_mutex_unlock(&control->last_meal_access);
	return ;
}

void	create_control(t_control *control, char **av)
{
	sem_unlink("/forks_sem");
	sem_unlink("/death_sem");
	sem_unlink("/stout_sem");
	control->nph = ft_atol(av[1]);
	control->time_to_die = ft_atol(av[2]) * 1000;
	control->time_to_eat = ft_atol(av[3]) * 1000;
	control->time_to_sleep = ft_atol(av[4]) * 1000;
	control->forks = sem_open("/forks_sem", O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO, control->nph);
	control->death_sem = sem_open("/death_sem", O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO, 0);
	control->stout_sem = sem_open("/stout_sem", O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO, 1);
}

int	create_children(t_control *control)
{
	int	i;
	int	pid;

	i = -1;
	while (++i < control->nph)
	{
	    pid = fork();
	    if (pid == 0)
		{
			control->phid = i + 1;
		    return (0);
		}
		else
		{
			if (!control->philov)
				control->philov = (int *)ph_calloc(sizeof(int), control->nph + 1);
			control->philov[i] = pid;
		}
	}
	return (pid);
}
