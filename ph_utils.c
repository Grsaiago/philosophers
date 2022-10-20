/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:56:43 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/20 19:23:10 by gsaiago          ###   ########.fr       */
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
	ptr = memset(ptr, 0, size * bytes);
	if (!ptr)
		return (NULL);
	return (ptr);
}

long int	get_time(struct timeval *tv)
{
	long int	current_time;

	gettimeofday(tv, NULL);
	current_time = ((tv->tv_sec * 1000000) + tv->tv_usec);
	return (current_time);
}

void	create_control(t_control *control, char **av)
{
	control->nph = ft_atol(av[1]); // the number of philosophers
	control->time_to_die = ft_atol(av[2]);
	control->last_meal = (long unsigned int *)ph_calloc(sizeof(long unsigned int), (control->nph + 1));
	control->thv = (pthread_t *)ph_calloc(sizeof(pthread_t *), control->nph + 1); // array in which every position will be a thread id
	control->philov = (t_philo **)ph_calloc(sizeof(t_philo *), control->nph + 1); // creating a vector with the address of every philo struct
	control->forkv = (pthread_mutex_t *)ph_calloc(sizeof(pthread_mutex_t), control->nph + 1); //create mutex vector to control everything, alongside the forkv
	control->death_access = ph_calloc(sizeof(pthread_mutex_t), control->nph + 1);
	control->time_to_die = ft_atol(av[2]);
	pthread_create(&control->vulture ,NULL, &vulture, control);
	return ;
}
