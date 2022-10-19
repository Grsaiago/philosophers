/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:56:43 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/19 18:11:32 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ph_calloc(int size, int bytes)
{
	void	*ptr;

	if (size <= 0 || bytes <= 0)
		return (NULL);
	ptr = malloc(size * bytes);
	if (!ptr)
		return (NULL);
	ptr = memset(ptr, 0, size * bytes);
	if (!ptr)
		return (NULL);
	return (ptr);
}

void	death_refresh(t_philo *philo)
{
	long unsigned int	current_time;

	gettimeofday(&philo->tv, NULL);
	current_time = ((philo->tv.tv_sec * 1000) + philo->tv.tv_usec / 1000);
	philo->mementomori[philo->phid - 1] = current_time;
	return ;
}

void	*vulture(void *ptr)
{
	long unsigned int	current_time;
	int					i;
	t_control			*control;

	control = (t_control *)ptr;
	i = 0;
	while (42)
	{
		if (i == control->nph)
			i = 0;
		gettimeofday(&control->tv, NULL);
		current_time = ((control->tv.tv_sec * 1000) + control->tv.tv_usec / 1000);
		printf("control->mementomori[%d] > |%ld|\n", i, control->mementomori[i]);
		printf("current_time> |%ld|\n",current_time);
		printf("current_time - control->mementomori[%d] > |%ld|\n", i, current_time - control->mementomori[i]);
		if (((current_time - control->mementomori[i]) >= control->time_to_die) && control->mementomori[i] != 0)
			break ;
		i++;
	}
	kill_threads(control);
	free_all(control);
	printf("Philosopher %d has died\n", i + 1);
	exit(1);
	return (NULL);
}

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
	if (control->mementomori)
		free(control->mementomori);
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
