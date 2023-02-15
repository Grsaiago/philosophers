/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_dinner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:05:11 by gsaiago           #+#    #+#             */
/*   Updated: 2023/02/14 21:16:06 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*dine(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	if (!philo)
		return (NULL);
	death_refresh(philo);
	while (42)
	{
		if (ph_think(philo) || ph_eat(philo) || ph_sleep(philo))
			break ;
	}
	return (NULL);
}

int	add_meal(t_philo *philo)
{
	if (!philo->max_eat)
		return (0);
	pthread_mutex_lock(&philo->times_eaten_access[philo->phindex]);
	philo->times_eaten[philo->phindex]++;
	pthread_mutex_unlock(&philo->times_eaten_access[philo->phindex]);
	return (0);
}

void	death_refresh(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_access[philo->phindex]);
	philo->last_meal[philo->phindex] = get_time(1);
	pthread_mutex_unlock(&philo->last_meal_access[philo->phindex]);
	return ;
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
