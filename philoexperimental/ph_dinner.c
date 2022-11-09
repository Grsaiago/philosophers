/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_dinner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:05:11 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/08 23:08:39 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	dine(t_philo *philo)
{
	death_refresh(philo);
	while (42)
	{
		if (ph_think(philo) || ph_eat(philo) || ph_sleep(philo))
			break ;
	}
	return ;
}

int	add_meal(t_philo *philo)
{
	if (philo->max_eat <= 0)
		return (0);
	philo->times_eaten++;
	if (philo->times_eaten > philo->max_eat)
		return (1);
	return (0);
}

void	death_refresh(t_philo *philo)
{
	long unsigned int	current_time;

	pthread_mutex_lock(&philo->last_meal_access[philo->phid - 1]);
	current_time = get_time(&philo->tv, 1);
	philo->last_meal[philo->phid - 1] = current_time;
	pthread_mutex_unlock(&philo->last_meal_access[philo->phid - 1]);
	return ;
}

int	take_forks(t_philo *philo)
{
	if (philo->phid == philo->nph)
	{
		pthread_mutex_lock(&philo->forkv[philo->prev_f]);
		if (stop_execution(philo))
		{
			pthread_mutex_unlock(&philo->forkv[philo->prev_f]);
			return (1);
		}
		printf("%ld %d has taken a fork\n",
			get_time(&philo->tv, 1000), philo->phid);
		pthread_mutex_lock(&philo->forkv[philo->next_f]);
		if (stop_execution(philo))
		{
			pthread_mutex_unlock(&philo->forkv[philo->prev_f]);
			pthread_mutex_unlock(&philo->forkv[philo->next_f]);
			return (1);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->forkv[philo->next_f]);
		if (stop_execution(philo))
		{
			pthread_mutex_unlock(&philo->forkv[philo->next_f]);
			return (1);
		}
		printf("%ld %d has taken a fork\n",
			get_time(&philo->tv, 1000), philo->phid);
		pthread_mutex_lock(&philo->forkv[philo->prev_f]);
		if (stop_execution(philo))
		{
			pthread_mutex_unlock(&philo->forkv[philo->prev_f]);
			pthread_mutex_unlock(&philo->forkv[philo->next_f]);
			return (1);
		}
	}
	return (0);
}

void	return_forks(t_philo *philo)
{
	if (philo->phid == philo->nph)
	{
		pthread_mutex_unlock(&philo->forkv[philo->prev_f]);
		pthread_mutex_unlock(&philo->forkv[philo->next_f]);
	}
	else
	{
		pthread_mutex_unlock(&philo->forkv[philo->next_f]);
		pthread_mutex_unlock(&philo->forkv[philo->prev_f]);
	}
	return ;
}
