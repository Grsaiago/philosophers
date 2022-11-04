/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_vulture_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:40:33 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/03 21:19:52 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*vulture_exec(void *ptr)
{
	t_control	*control;

	control = (t_control *)ptr;
	while (42)
	{
		still_alive(control);
		stop_eating(control);
	}
	return (NULL);
}

void	vulture_create(t_control *control)
{
	pthread_mutex_init(&control->last_meal_access, NULL);
	pthread_mutex_init(&control->times_eaten_access, NULL);
	pthread_create(&control->vulture_thread, NULL,
		&vulture_exec, control);
	pthread_detach(control->vulture_thread);
}

void	still_alive(t_control *control)
{
	int			i;
	long int	diff;
	long int	current_time;

	pthread_mutex_lock(&control->last_meal_access);
	current_time = get_time(&control->tv_last_meal, 1);
	diff = current_time - control->last_meal;
	if (diff > control->time_to_die && (control->last_meal != 0))
	{
		current_time = get_time(&control->tv_last_meal, 1000);
		sem_wait(control->stout_sem);
		printf("%ld %d has died\n", current_time, control->phid);
		pthread_mutex_unlock(&control->last_meal_access);
		i = -1;
		while (++i < control->nph)
			sem_post(control->death_sem);
	}
	pthread_mutex_unlock(&control->last_meal_access);
}

void	stop_eating(t_control *control)
{
	if (control->max_eat <= 0)
		return ;
	pthread_mutex_lock(&control->times_eaten_access);
	if (control->times_eaten >= control->max_eat)
	{
		pthread_mutex_unlock(&control->times_eaten_access);
		control->max_eat = 0;
		sem_post(control->death_sem);
	}
	pthread_mutex_unlock(&control->times_eaten_access);
}
