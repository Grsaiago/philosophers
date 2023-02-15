/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:29:22 by gsaiago           #+#    #+#             */
/*   Updated: 2023/02/14 21:09:00 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_func(t_control *control)
{
//	kill_mutexes(control);
	free_all(control);
	return ;
}

void	free_all(t_control *control)
{
	int		i;

	i = 0;
	free(control->last_meal_access);
	free(control->last_meal);
	while (i < control->nph)
	{
		if (control->philov[i])
			free(control->philov[i]);
		i++;
	}
	free(control->philov);
	free(control->thv);
	free(control->times_eaten);
	free(control->times_eaten_access);
	free(control->fork_state);
	free(control->fork_state_access);
	free(control->stop_eating);
	free(control->stop_eating_access);
	return ;
}

void	kill_mutexes(t_control *control)
{
	int	i;

	i = 0;
	while (i < control->nph)
	{
		pthread_mutex_destroy(&control->last_meal_access[i]);
		pthread_mutex_destroy(&control->fork_state_access[i]);
		i++;
	}
	pthread_mutex_destroy(control->stop_eating_access);
	return ;
}
