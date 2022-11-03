/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_vulture_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:40:33 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/03 17:02:17 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*vulture_exec(void *ptr)
{
	t_control	*control;
	long int	diff;
	long int	current_time;

	control = (t_control *)ptr;
	while (42)
	{
		pthread_mutex_lock(&control->last_meal_access);
		current_time = get_time(&control->tv_last_meal, 1);
		diff = current_time - control->last_meal;
		if (diff > control->time_to_die && (control->last_meal != 0))
		{
			current_time = get_time(&control->tv_last_meal, 100);
			printf("%ld %d has died\n", current_time, control->phid);
			pthread_mutex_unlock(&control->last_meal_access);
			sem_post(control->death_sem);
			return (NULL);
		}
		else
			pthread_mutex_unlock(&control->last_meal_access);
	}
	return (NULL);
}

void	vulture_create(t_control *control)
{
	pthread_mutex_init(&control->last_meal_access, NULL);
	pthread_create(&control->vulture_thread, NULL,
			&vulture_exec, control); 
	pthread_detach(control->vulture_thread);
}
