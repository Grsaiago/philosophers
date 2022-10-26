/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:46:10 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/26 17:40:21 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int			i;
	int			*vulture_ret;
	t_control	*control;

	i = 0;
	control = &(t_control){0}; // main control struct with info
	validate_args(argc, argv);
	if (argc == 5)
		create_control(control, argv, 0);
	else
		create_control(control, argv, 1);
	pthread_create(&control->vulture, NULL, &vulture, control);
	initialize_mutex_struct_thread(control, argv);
	pthread_join(control->vulture, NULL);
	exit_func(control);
	return (0);
}

void	initialize_mutex_struct_thread(t_control *control, char **av)
{
	int	i;

	i = -1;
	while (++i < control->nph) // initialize mutexes.
	{
		pthread_mutex_init(&control->forkv[i], NULL);
		pthread_mutex_init(&control->last_meal_access[i], NULL);
		pthread_mutex_init(&control->times_eaten_access[i], NULL);
	}
	i = -1;
	while (++i < control->nph)
		control->philov[i] = create_thread_struct(control, i + 1, av);
	i = -1;
	pthread_mutex_lock(&control->mutex);
	while (++i < control->nph)
	{
		pthread_create(&control->thv[i], NULL,
			&thread_execute, control->philov[i]);
		pthread_detach(control->thv[i]);
	}
	pthread_mutex_unlock(&control->mutex);
	return ;
}
