/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_vulture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:38:57 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/08 22:49:10 by gsaiago          ###   ########.fr       */
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

int	if_dead(t_control *control, int i)
{
	long int	diff;
	long int	current_time;

	current_time = get_time(&control->tv, 1);
	diff = current_time - control->last_meal[i];
	if (diff > control->time_to_die && (control->last_meal[i] != 0))
	{
		pthread_mutex_lock(control->stop_eating_access);
		*control->stop_eating = 1;
		pthread_mutex_unlock(control->stop_eating_access);
		current_time = get_time(&control->tv, 1000);
		printf("%ld %d has died\n", current_time, i + 1);
		return (1);
	}
	return (0);
}
