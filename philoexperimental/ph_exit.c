/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:29:22 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/15 18:37:52 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_func(t_control *control)
{
	kill_vulture(control);
	kill_mutexes(control);
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
	free(control->forkv);
	free(control->fork_state);
	free(control->fork_state_access);
	free(control->stop_eating);
	free(control->stop_eating_access);
	free(control->vulture_return_access);
	free(control->vulture_return);
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

void	kill_vulture(t_control *control)
{
	pthread_mutex_lock(control->vulture_return_access);
	*control->vulture_return = 1;
	pthread_mutex_unlock(control->vulture_return_access);
	pthread_join(control->vulture, NULL);
}
