/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:56:43 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/26 17:41:39 by gsaiago          ###   ########.fr       */
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
	ptr = memset(ptr, 0, (size * bytes) - 1);
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

void	create_control(t_control *control, char **av, int if_times_eat)
{
	control->nph = ft_atol(av[1]);
	control->time_to_die = ft_atol(av[2]) * 1000;
	control->last_meal_access = (pthread_mutex_t *)
		ph_calloc(sizeof(pthread_mutex_t), control->nph + 1);
	control->last_meal = (long unsigned int *)
		ph_calloc(sizeof(long int), (control->nph + 1));
	control->times_eaten_access = (pthread_mutex_t *)
		ph_calloc(sizeof(pthread_mutex_t), control->nph + 1);
	control->times_eaten = (int *)ph_calloc(sizeof(int), control->nph + 1);
	control->philov = (t_philo **)
		ph_calloc(sizeof(t_philo *), control->nph + 1);
	control->forkv = (pthread_mutex_t *)
		ph_calloc(sizeof(pthread_mutex_t), control->nph + 1);
	control->thv = (pthread_t *)
		ph_calloc(sizeof(pthread_t *), control->nph + 1);
	if (if_times_eat)
		control->max_eat = ft_atol(av[5]);
	else
		control->max_eat = 0;
	return ;
}
