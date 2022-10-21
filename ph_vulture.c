/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_vulture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:38:57 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/21 20:31:21 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*time_vulture(void *ptr)
{
	long int	current_time;
	long int	diff;
	int			i;
	int			all_eat;
	t_control	*control;

	control = (t_control *)ptr;
	all_eat = 0;
	i = 0;
	while (42)
	{
		if (all_eat == control->nph - 1)
		{
			current_time = get_time(&control->tv, 100);
			printf("%ld Everyone has eaten!\n", current_time);
			break ;
		}
		if (i == control->nph)
		{
			all_eat = 0;
			i = 0;
		}
		pthread_mutex_lock(&control->death_access[i]);
		current_time = get_time(&control->tv, 1);
		diff = current_time - control->last_meal[i];
		if (diff > control->time_to_die && (control->last_meal[i] != 0))
		{
			printf("%ld %d has died\n", current_time, i + 1);
			break ;
		}
		if (control->times_eaten[i] >= control->max_eat && control->max_eat > 0)
			all_eat++;
		pthread_mutex_unlock(&control->death_access[i]);
		i++;
	}
	pthread_mutex_unlock(&control->death_access[i]);
	current_time = get_time(&control->tv, 100);
	exit_func(control);
	return (NULL);
}
