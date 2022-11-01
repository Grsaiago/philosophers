/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:05:11 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/28 11:08:00 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	dine(t_philo *philo)
{
	long int	time;

	death_refresh(philo);
	while (42)
	{
		time = get_time(&philo->tv, 100);
		printf("%ld %d is thinking\n", time, philo->phid);
		take_forks(philo);
		death_refresh(philo);
		time = get_time(&philo->tv, 100);
		printf("%ld %d is eating\n", time, philo->phid);
		usleep(philo->time_to_eat);
		if (philo->max_eat > 0)
			add_meal(philo);
		return_forks(philo);
		time = get_time(&philo->tv, 100);
		printf("%ld %d is sleeping\n", time, philo->phid);
		usleep(philo->time_to_sleep);
	}
	return ;
}

void	add_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->times_eaten_access[philo->phid - 1]);
	philo->times_eaten[philo->phid - 1]++;
	pthread_mutex_unlock(&philo->times_eaten_access[philo->phid - 1]);
	return ;
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

void	take_forks(t_philo *philo)
{
	long int	time;

	if (philo->phid == philo->nph)
	{
		pthread_mutex_lock(&philo->forkv[philo->prev_f]);
		time = get_time(&philo->tv, 100);
		printf("%ld %d has taken a fork\n", time, philo->phid);
		pthread_mutex_lock(&philo->forkv[philo->next_f]);
	}
	else
	{
		pthread_mutex_lock(&philo->forkv[philo->next_f]);
		time = get_time(&philo->tv, 100);
		printf("%ld %d has taken a fork\n", time, philo->phid);
		pthread_mutex_lock(&philo->forkv[philo->prev_f]);
	}
	return ;
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
