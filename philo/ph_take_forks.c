/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_take_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:42:46 by gsaiago           #+#    #+#             */
/*   Updated: 2023/02/14 21:26:03 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *philo)
{
	if (philo->is_even)
	{
		if (even_philo_fork_take(philo))
			return (1);
	}
	else
	{
		if (odd_philo_fork_take(philo))
			return (1);
	}
	return (0);
}

void	return_forks(t_philo *philo)
{
	if (philo->is_even)
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

int	even_philo_fork_take(t_philo *philo)
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
	return (0);
}

int	odd_philo_fork_take(t_philo *philo)
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
	return (0);
}
