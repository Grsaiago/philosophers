/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_vulture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:38:57 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/14 19:34:55 by gsaiago          ###   ########.fr       */
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
		if (stop_eating(control))
			return (NULL);
		pthread_mutex_lock(&control->last_meal_access[i]);
		if (if_dead(control, i))
		{
			pthread_mutex_unlock(&control->last_meal_access[i]);
			break ;
		}
		pthread_mutex_unlock(&control->last_meal_access[i]);
		i++;
	}
	return (NULL);
}

int	stop_eating(t_control *control)
{
	int			i;
	long int	current_time;

	i = 0;
	if (control->max_eat < 0)
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
	current_time = get_time(&control->tv, 1000);
	printf("%ld Everyone has eaten!\n", current_time);
	return (1);
}

int	if_dead(t_control *control, int i)
{
	long int	diff;
	long int	current_time;

	current_time = get_time(&control->tv, 1);
	diff = current_time - control->last_meal[i];
	if (diff > control->time_to_die && (control->last_meal[i] != 0))
	{
		current_time = get_time(&control->tv, 1000);
		printf("%ld %d has died\n", current_time, i + 1);
		return (1);
	}
	return (0);
}
