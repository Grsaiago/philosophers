/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_think_eat_sleep.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:20:48 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/10 19:03:27 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_think(t_philo *philo)
{
	if (stop_execution(philo))
		return (1);
	printf("%ld %d is thinking\n", get_time(&philo->tv, 1000), philo->phid);
	return (0);
}

int	ph_eat(t_philo *philo)
{
	if (stop_execution(philo))
		return (1);
	if (take_forks(philo))
		return (1);
	death_refresh(philo);
	printf("%ld %d is eating\n", get_time(&philo->tv, 1000), philo->phid);
	usleep(philo->time_to_eat);
	return_forks(philo);
	if (add_meal(philo))
		return (1);
	return (0);
}

int	ph_sleep(t_philo *philo)
{
	if (stop_execution(philo))
		return (1);
	printf("%ld %d is sleeping\n", get_time(&philo->tv, 1000), philo->phid);
	usleep(philo->time_to_sleep);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->phid == philo->nph)
	{
		while (42)
		{
			if (trylock_fork(philo, philo->prev_f))
				break ;
			if (stop_execution(philo))
				return (1);
		}
		while (42)
		{
			if (trylock_fork(philo, philo->next_f))
				break ;
			if (stop_execution(philo))
				return (1);
		}
	}
	else
	{
		while (42)
		{
			if (trylock_fork(philo, philo->next_f))
				break ;
			if (stop_execution(philo))
				return (1);
		}
		while (42)
		{
			if (trylock_fork(philo, philo->prev_f))
				break ;
			if (stop_execution(philo))
				return (1);
		}
	}
	return (0);
}

void	return_forks(t_philo *philo)
{
	if (philo->phid == philo->nph)
	{
		ph_unlock_fork(philo, philo->prev_f);
		ph_unlock_fork(philo, philo->next_f);
	}
	else
	{
		ph_unlock_fork(philo, philo->next_f);
		ph_unlock_fork(philo, philo->prev_f);
	}
	return ;
}
