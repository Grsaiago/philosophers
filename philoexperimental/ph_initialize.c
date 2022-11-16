/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:54:59 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/15 20:18:58 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_control(t_control *control, char **av, int if_times_eat)
{
	control->nph = ft_atol(av[1]);
	control->time_to_die = ft_atol(av[2]) * 1000;
	control->last_meal_access = (pthread_mutex_t *)
		ph_calloc(sizeof(pthread_mutex_t), control->nph + 1);
	control->last_meal = ph_calloc(sizeof(long int), (control->nph + 1));
	control->philov = ph_calloc(sizeof(t_philo *), control->nph + 1);
	control->forkv = (pthread_mutex_t *)
		ph_calloc(sizeof(pthread_mutex_t), control->nph + 1);
	control->thv = (pthread_t *)
		ph_calloc(sizeof(pthread_t *), control->nph + 1);
	control->stop_eating_access = (pthread_mutex_t *)
		ph_calloc(sizeof(pthread_mutex_t), 1);
	control->stop_eating = (int *)ph_calloc(sizeof(int), 1);
	control->fork_state = (int *)ph_calloc(sizeof(int), ft_atol(av[1]));
	control->fork_state_access = (pthread_mutex_t *)
		ph_calloc(sizeof(pthread_mutex_t), control->nph + 1);
	control->vulture_return_access = (pthread_mutex_t *)
		ph_calloc(sizeof(pthread_mutex_t), 1);
	control->vulture_return = ph_calloc(sizeof(char), 1);
	if (if_times_eat)
		control->max_eat = ft_atol(av[5]);
	else
		control->max_eat = 0;
	return ;
}

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
	philo->phid = i;
	philo->stop_eating_access = control->stop_eating_access;
	philo->stop_eating = control->stop_eating;
	philo->fork_state = control->fork_state;
	philo->fork_state_access = control->fork_state_access;
	philo->prev_f = i - 1;
	philo->next_f = i;
	if (philo->next_f == control->nph)
		philo->next_f = 0;
	return (philo);
}

void	initialize_mutex_struct_thread(t_control *control, char **av)
{
	int	i;

	i = -1;
	while (++i < control->nph)
	{
		pthread_mutex_init(&control->forkv[i], NULL);
		pthread_mutex_init(&control->fork_state_access[i], NULL);
		pthread_mutex_init(&control->last_meal_access[i], NULL);
	}
	pthread_mutex_init(control->vulture_return_access, NULL);
	pthread_mutex_init(control->stop_eating_access, NULL);
	i = -1;
	while (++i < control->nph)
		control->philov[i] = create_thread_struct(control, i + 1, av);
	i = -1;
	while (++i < control->nph)
	{
		pthread_create(&control->thv[i], NULL,
			&dine, control->philov[i]);
	}
	pthread_create(&control->vulture, NULL, &vulture, control);
	return ;
}
