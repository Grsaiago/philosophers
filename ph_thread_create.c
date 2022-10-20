/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:43:46 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/20 16:44:32 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_thread_struct(t_control *control, int i, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		exit (1);
	philo->nph = control->nph;
	philo->forkv = control->forkv;
	philo->death_access = control->death_access;
	philo->last_meal = control->last_meal;
	philo->time_to_eat = atoi(av[3]);
	philo->time_to_sleep = atoi(av[4]);
	philo->phid = i;
	philo->prev_f = i - 1;
	philo->next_f = i;
	if (philo->next_f >= control->nph)
		philo->next_f = philo->next_f % control->nph;
	return(philo);
}
