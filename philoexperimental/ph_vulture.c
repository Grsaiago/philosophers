/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_vulture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:38:57 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/15 18:38:10 by gsaiago          ###   ########.fr       */
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
		if (check_philo_death(control, i))
			return (NULL);
		if (check_vulture_return(control))
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
	current_time = get_time(&control->tv, 1);
	diff = current_time - control->last_meal[i];
	if (diff > control->time_to_die && control->last_meal[i])
	{
		pthread_mutex_lock(control->stop_eating_access);
		*control->stop_eating = 1;
		pthread_mutex_unlock(control->stop_eating_access);
		printf("%ld %d has died\n", get_time(&control->tv, 1000), i + 1);
		pthread_mutex_unlock(&control->last_meal_access[i]);
		return (1);
	}
	pthread_mutex_unlock(&control->last_meal_access[i]);
	return (0);
}

int	check_vulture_return(t_control *control)
{
	pthread_mutex_lock(control->vulture_return_access);
	if (*control->vulture_return)
	{
		pthread_mutex_unlock(control->vulture_return_access);
		return (1);
	}
	pthread_mutex_unlock(control->vulture_return_access);
	return (0);
}
