/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:09:51 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/03 21:18:13 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	int			i;
	int			pid;
	t_control	*control;	

	control = &(t_control){0};
	if (validate_args(argc, argv))
		return (0);
	if (argc == 5)
		create_control(control, argv, 0);
	else
		create_control(control, argv, 1);
	pid = create_children(control);
	if (pid == 0)
	{
		vulture_create(control);
		dine(control);
	}
	i = -1;
	while (++i < control->nph)
		sem_wait(control->death_sem);
	exit_func(control);
	return (0);
}
