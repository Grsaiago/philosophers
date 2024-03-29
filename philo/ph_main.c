/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:46:10 by gsaiago           #+#    #+#             */
/*   Updated: 2023/02/18 18:48:38 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int			i;
	t_control	*control;

	control = &(t_control){0};
	i = 0;
	if (validate_args(argc, argv))
		return (EXIT_FAILURE);
	if (argc == 5)
		create_control(control, argv, 0);
	else
		create_control(control, argv, 1);
	initialize_mutex_struct_thread(control, argv);
	pthread_join(control->vulture, NULL);
	while (i < control->nph)
	{
		pthread_join(control->thv[i], NULL);
		i++;
	}
	exit_func(control);
	return (0);
}
