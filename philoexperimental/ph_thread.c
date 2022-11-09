/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:41:13 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/08 22:24:48 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_thread_struct(t_control *control, int i, char **av)
{
	t_philo	*philo;

	philo = ph_calloc(sizeof(t_philo), 1);
	if (!philo)
	philo->nph = control->nph;
	philo->time_to_eat = ft_atol(av[3]) * 1000;
	philo->time_to_sleep = ft_atol(av[4]) * 1000;
	philo->max_eat = control->max_eat;
	philo->forkv = control->forkv;
	philo->last_meal_access = control->last_meal_access;
	philo->last_meal = control->last_meal;
	philo->phid = i;
	philo->prev_f = i - 1;
	philo->next_f = i;
	philo->stop_eating_access = control->stop_eating_access;
	philo->stop_eating = control->stop_eating;
	if (philo->next_f == control->nph)
		philo->next_f = 0;
	return (philo);
}

int	stop_execution(t_philo	*philo)
{
	pthread_mutex_lock(philo->stop_eating_access);
	if (*philo->stop_eating)
	{
		pthread_mutex_unlock(philo->stop_eating_access);
		return (1);
	}
	pthread_mutex_unlock(philo->stop_eating_access);
	return (0);
}

void	*thread_execute(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	dine(philo);
	return (NULL);
}
