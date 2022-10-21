/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:46:10 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/21 19:50:27 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int					i;
	t_control			*control;

	i = 0;
	control = &(t_control){0}; // main control struct with info
	validate_args(argc, argv);
	if (argc == 5)
		create_control(control, argv, 0); // tem que ver como fica a parte do vulture aqui dentro.
	else
		create_control(control, argv, 1); // tem que ver como fica a parte do vulture aqui dentro.
	while (i < control->nph) // initialize mutexes.
	{
		pthread_mutex_init(&control->forkv[i], NULL);
		pthread_mutex_init(&control->death_access[i], NULL);
		i++;
	}
	i = -1;
	while (++i < control->nph)
		control->philov[i] = create_thread_struct(control, i + 1, argv);
	i = -1;
	// até aqui dá pra reaproveitar em.
	pthread_mutex_lock(&control->mutex);
	while (++i < control->nph)
		pthread_create(&control->thv[i], NULL, &thread_execute, control->philov[i]);
	pthread_mutex_unlock(&control->mutex);
	i = -1;
	while (++i < control->nph)
		pthread_join(control->thv[i], NULL);
	return (0);
}
