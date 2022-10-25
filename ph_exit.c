/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:36:27 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/25 16:39:37 by gsaiago          ###   ########.fr       */
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
	if (control->times_eaten_access)
		free(control->times_eaten_access);
	if (control->times_eaten)
		free(control->times_eaten);
	while (i < control->nph)
	{
		free(control->philov[i]);
		i++;
	}
	if (control->philov)
		free(control->philov);
	if (control->thv)
		free(control->thv);
	if (control->forkv)
		free(control->forkv);
}

void	kill_mutexes(t_control *control)
{
	int	i;

	i = 0;
	while (i < control->nph)
	{
		pthread_mutex_destroy(&control->last_meal_access[i]);
		pthread_mutex_destroy(&control->times_eaten_access[i]);
		pthread_mutex_destroy(&control->forkv[i]);
		i++;
	}
	pthread_mutex_destroy(&control->mutex);
	return ;
}

void	exit_func(t_control *control)
{
//	kill_mutexes(control);
//	free_all(control);
	return ;
}
