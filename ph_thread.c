/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:40:16 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/25 16:38:05 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_thread_struct(t_control *control, int i, char **av)
{
	t_philo	*philo;

	philo = ph_calloc(sizeof(t_philo), 1);
	if (!philo)
	philo->nph = control->nph;
	philo->time_to_eat = ft_atol(av[3]) * 1000;
	philo->time_to_sleep = ft_atol(av[4]) * 1000;
	philo->max_eat = control->max_eat;
	philo->forkv = control->forkv;
	philo->last_meal_access = control->last_meal_access;
	philo->last_meal = control->last_meal;
	philo->times_eaten_access = control->times_eaten_access;
	philo->times_eaten = control->times_eaten;
	philo->phid = i;
	philo->prev_f = i - 1;
	philo->next_f = i;
	if (philo->next_f == control->nph)
		philo->next_f = 0;
	return(philo);
}

void	*thread_execute(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	dine(philo); // if fifth_arg == 1
	return (NULL);
}

void	dine(t_philo *philo)
{
	long int time;

	death_refresh(philo);
	while (42)
	{
		time = get_time(&philo->tv, 100);
		printf("%ld %d is thinking\n",time, philo->phid);
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
		death_refresh(philo);
		time = get_time(&philo->tv, 100);
		printf("%ld %d is eating\n", time, philo->phid);
		usleep(philo->time_to_eat);
		if (philo->max_eat > 0)
			dine_add (philo);
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
		time = get_time(&philo->tv, 100);
		printf("%ld %d is sleeping\n", time, philo->phid);
		usleep(philo->time_to_sleep);
	}
	return ;
}

void	dine_add(t_philo *philo)
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
