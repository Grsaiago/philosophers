/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:40:16 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/20 16:44:54 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*thread_execute(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	dine(philo);
	return (NULL);
}

void	dine(t_philo *philo)
{
	death_refresh(philo);
	while (42)
	{
		if (philo->phid == philo->nph)
		{
			pthread_mutex_lock(&philo->forkv[philo->prev_f]);
			printf("%d has taken a fork\n", philo->phid);
			pthread_mutex_lock(&philo->forkv[philo->next_f]);
		}
		else 
		{
			pthread_mutex_lock(&philo->forkv[philo->next_f]);
			printf("%d has taken a fork\n", philo->phid);
			pthread_mutex_lock(&philo->forkv[philo->prev_f]);
		}
		printf("%d is eating\n", philo->phid);
		usleep(philo->time_to_eat);
		death_refresh(philo);
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
		printf("%d is thinking\n", philo->phid);
		usleep(300);
	}
}

void	death_refresh(t_philo *philo)
{
	long unsigned int	current_time;

	pthread_mutex_lock(&philo->death_access[philo->phid - 1]);
	gettimeofday(&philo->tv, NULL);
	current_time = ((philo->tv.tv_sec * 1000) + philo->tv.tv_usec / 1000);
	philo->last_meal[philo->phid - 1] = current_time;
	pthread_mutex_unlock(&philo->death_access[philo->phid - 1]);
	return ;
}
