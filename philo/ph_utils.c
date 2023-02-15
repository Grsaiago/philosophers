/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:56:43 by gsaiago           #+#    #+#             */
/*   Updated: 2023/02/14 21:39:38 by gsaiago          ###   ########.fr       */
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

long int	get_time(int i)
{
	long int		current_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = ((tv.tv_sec * 1000000) + tv.tv_usec);
	return (current_time / i);
}

int	trylock_fork(t_philo *philo, int n_fork)
{
	if (!philo || n_fork < 0)
		return (0);
	pthread_mutex_lock(&philo->fork_state_access[n_fork]);
	if (!philo->fork_state[n_fork])
	{
		philo->fork_state[n_fork] = 1;
		pthread_mutex_unlock(&philo->fork_state_access[n_fork]);
		printf("%ld %d has taken a fork\n",
			get_time(1000), philo->phid);
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
	return ;
}

int		smart_sleep(t_philo *philo, long unsigned int usec)
{
	long int	end;

	end = get_time(1) + usec;
	while (end > get_time(1))
	{
		usleep(100);
		if (stop_execution(philo))
			return (1);
	}
	return (0);
}
