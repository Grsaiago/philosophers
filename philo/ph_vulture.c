/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_vulture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:38:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/02/14 23:03:41 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*vulture(void *ptr)
{
	int			i;
	t_control	*control;

	control = (t_control *)ptr;
	i = 0;
	while (42)
	{
		if (i == control->nph)
			i = 0;
		if (check_philo_death(control, i) || check_eaten_times(control))
			return (NULL);
		i++;
	}
	return (NULL);
}

int	check_philo_death(t_control *control, int i)
{
	long int	diff;
	long int	current_time;

	pthread_mutex_lock(&control->last_meal_access[i]);
	current_time = get_time(1);
	diff = current_time - control->last_meal[i];
	if (diff > control->time_to_die && control->last_meal[i])
	{
		pthread_mutex_lock(control->stop_eating_access);
		*control->stop_eating = 1;
		pthread_mutex_unlock(control->stop_eating_access);
		printf("%ld %d has died\n", get_time(1000), i + 1);
		pthread_mutex_unlock(&control->last_meal_access[i]);
		return (1);
	}
	pthread_mutex_unlock(&control->last_meal_access[i]);
	return (0);
}

int	check_eaten_times(t_control *control)
{
	int	i;

	i = 0;
	if (!control->max_eat)
		return (0);
	while (i < control->nph)
	{
		pthread_mutex_lock(&control->times_eaten_access[i]);
		if (control->times_eaten[i] < control->max_eat)
		{
			pthread_mutex_unlock(&control->times_eaten_access[i]);
			return (0);
		}
		pthread_mutex_unlock(&control->times_eaten_access[i]);
		i++;
	}
	pthread_mutex_lock(control->stop_eating_access);
	*control->stop_eating = 1;
	pthread_mutex_unlock(control->stop_eating_access);
	return (1);
}
