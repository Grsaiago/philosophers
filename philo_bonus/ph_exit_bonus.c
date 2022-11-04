/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_exit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:22:00 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/03 21:17:53 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	exit_func(t_control *control)
{
	int	i;

	i = 0;
	while (i < control->nph)
	{
		kill(control->philov[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i < control->nph)
	{
		waitpid(control->philov[i], NULL, 0);
		i++;
	}
	if (control->philov)
		free(control->philov);
	sem_close(control->forks);
	sem_close(control->death_sem);
	sem_close(control->stout_sem);
	sem_unlink("/forks_sem");
	sem_unlink("/death_sem");
	sem_unlink("/stout_sem");
}
