/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:56:43 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/10 20:12:47 by gsaiago          ###   ########.fr       */
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
	ptr = memset(ptr, 0, (size * bytes));
	if (!ptr)
		return (NULL);
	return (ptr);
}

long int	get_time(struct timeval *tv, int i)
{
	long int	current_time;

	gettimeofday(tv, NULL);
	current_time = ((tv->tv_sec * 1000000) + tv->tv_usec);
	return (current_time / i);
}

int	trylock_fork(t_philo *philo, int n_fork)
{
	if (!philo || n_fork < 0)
		return (0);
	pthread_mutex_lock(&philo->fork_state_access[n_fork]);
	if (!philo->fork_state[n_fork])
	{
		pthread_mutex_lock(&philo->forkv[n_fork]);
		philo->fork_state[n_fork] = 1;
		pthread_mutex_unlock(&philo->fork_state_access[n_fork]);
		printf("%ld %d has taken a fork\n",
			get_time(&philo->tv, 1000), philo->phid);
		return (1);
	}
	pthread_mutex_unlock(&philo->fork_state_access[n_fork]);
	return (0);
}

void	ph_unlock_fork(t_philo *philo, int n_fork)
{
	if (!philo || n_fork < 0)
		return ;
	pthread_mutex_lock(&philo->fork_state_access[n_fork]);
	philo->fork_state[n_fork] = 0;
	pthread_mutex_unlock(&philo->fork_state_access[n_fork]);
	pthread_mutex_unlock(&philo->forkv[n_fork]);
	return ;
}
