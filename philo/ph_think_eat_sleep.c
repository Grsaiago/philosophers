/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_think_eat_sleep.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:20:48 by gsaiago           #+#    #+#             */
/*   Updated: 2023/02/14 21:40:32 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_think(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_time(1000), philo->phid);
	return (0);
}

int	ph_eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	death_refresh(philo);
	printf("%ld %d is eating\n", get_time(1000), philo->phid);
	if(smart_sleep(philo, philo->time_to_eat))
		return (1);
	return_forks(philo);
	add_meal(philo);
	return (0);
}

int	ph_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time(1000), philo->phid);
	if(smart_sleep(philo, philo->time_to_sleep))
		return (1);
	return (0);
}
