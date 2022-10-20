/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:36:27 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/20 18:43:10 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_control *control)
{
	int		i;

	i = 0;
	while (i < control->nph)
	{
		free(control->philov[i]);
		i++;
	}
	if (control->philov)
		free(control->philov);
	if (control->thv)
		free(control->thv);
	if (control->last_meal)
		free(control->last_meal);
	if (control->forkv)
		free(control->forkv);
}

void	kill_threads(t_control	*control)
{
	int	i;

	i = 0;
	if (!control->thv)
		return ;
	while (i < control->nph)
	{
		if (control->thv[i])
			pthread_detach(control->thv[i]);
		i++;
	}
	return ;
}

void	kill_mutexes(t_control *control)
{
	int	i;

	i = 0;
	if (control->death_access)
	{
		while (i < control->nph)
		{
			pthread_mutex_destroy(&control->death_access[i]);
			i++;
		}
	}
	i = 0;
	if (control->forkv)
	{
		while (i < control->nph)
		{
			pthread_mutex_destroy(&control->forkv[i]);
			i++;
		}
	}
	return ;
}

void	exit_func(t_control *control)
{
	kill_threads(control);
	kill_mutexes(control);
	free_all(control);
	exit (1);
	return ;
}
