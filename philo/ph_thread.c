/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:41:13 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/28 11:31:14 by gsaiago          ###   ########.fr       */
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
	philo->times_eaten_access = control->times_eaten_access;
	philo->times_eaten = control->times_eaten;
	philo->phid = i;
	philo->prev_f = i - 1;
	philo->next_f = i;
	if (philo->next_f == control->nph)
		philo->next_f = 0;
	return (philo);
}

void	*thread_execute(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	dine(philo);
	return (NULL);
}
