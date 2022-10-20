/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:40:16 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/20 19:53:57 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_thread_struct(t_control *control, int i, char **av)
{
	t_philo	*philo;

	philo = ph_calloc(sizeof(t_philo), 1);
	if (!philo)
		exit (1);
	philo->nph = control->nph;
	philo->forkv = control->forkv;
	philo->death_access = control->death_access;
	philo->last_meal = control->last_meal;
	philo->time_to_eat = ft_atol(av[3]) * 1000;
	philo->time_to_sleep = ft_atol(av[4]) * 1000;
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
	dine(philo);
	return (NULL);
}

void	dine(t_philo *philo)
{
	long int time;
	death_refresh(philo);
	while (42)
	{
		printf("%d is thinking\n",philo->phid);
		usleep(150);
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
		death_refresh(philo);
		usleep(philo->time_to_eat);
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
		printf("%d is sleeping\n", philo->phid);
		usleep(philo->time_to_sleep);
	}
}

void	death_refresh(t_philo *philo)
{
	long unsigned int	current_time;

	pthread_mutex_lock(&philo->death_access[philo->phid - 1]);
	current_time = get_time(&philo->tv);
	philo->last_meal[philo->phid - 1] = current_time;
	pthread_mutex_unlock(&philo->death_access[philo->phid - 1]);
	return ;
}
