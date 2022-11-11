/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:29:22 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/10 21:05:43 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_control *control)
{
	int		i;

	i = 0;
	if (control->last_meal_access)
		free(control->last_meal_access);
	if (control->last_meal)
		free(control->last_meal);
	while (i < control->nph)
	{
		if (control->philov[i])
			free(control->philov[i]);
		i++;
	}
	if (control->philov)
		free(control->philov);
	if (control->thv)
		free(control->thv);
	if (control->forkv)
		free(control->forkv);
	if (control->fork_state)
		free(control->fork_state);
	if (control->fork_state_access)
		free(control->fork_state_access);
	if (control->stop_eating)
		free(control->stop_eating);
	if (control->stop_eating_access)
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
		if (control->fork_state[i])
			pthread_mutex_unlock(&control->forkv[i]);
		pthread_mutex_destroy(&control->forkv[i]);
		i++;
	}
	pthread_mutex_destroy(control->stop_eating_access);
	return ;
}

void	exit_func(t_control *control)
{
	kill_mutexes(control);
	free_all(control);
	return ;
}
