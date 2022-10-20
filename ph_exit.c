/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:36:27 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/20 16:38:19 by gsaiago          ###   ########.fr       */
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
	i = 0;
	while (i < control->nph)
	{
		pthread_mutex_destroy(&control->forkv[i]);
		i++;
	}
	if (control->forkv)
		free(control->forkv);
}

void	kill_threads(t_control	*control)
{
	int	i;

	i = 0;
	while (i < control->nph)
	{
		pthread_detach(control->thv[i]);
		i++;
	}
	return ;
}
