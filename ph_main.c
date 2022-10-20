/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:46:10 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/20 16:23:12 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_thread_struct(t_control *control, int i, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		exit (1);
	philo->nph = control->nph;
	philo->forkv = control->forkv;
	philo->death_access = control->death_access;
	philo->last_meal = control->last_meal;
	philo->time_to_eat = atoi(av[3]);
	philo->time_to_sleep = atoi(av[4]);
	philo->phid = i;
	philo->prev_f = i - 1;
	philo->next_f = i;
	if (philo->next_f >= control->nph)
		philo->next_f = philo->next_f % control->nph;
	return(philo);
}

void	*thread_execute(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	dine(philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	int					i;
	t_control			*control;
	pthread_mutex_t		mutex;

	i = 0;
	control = &(t_control){0}; // main control struct with info
	validate_args(argc, argv);
	create_control(control, argv);
	while (i < control->nph) // initialize mutexes
	{
		pthread_mutex_init(&control->forkv[i], NULL);
		pthread_mutex_init(&control->death_access[i], NULL);
		i++;
	}
	i = -1;
	while (++i < control->nph)
		control->philov[i] = create_thread_struct(control, i + 1, argv);
	i = -1;
	while (++i < control->nph)
		pthread_create(&control->thv[i], NULL, &thread_execute, control->philov[i]);
	i = -1;
	while (++i < control->nph)
		pthread_join(control->thv[i], NULL);
	return (0);
}
