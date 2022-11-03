/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:09:51 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/03 17:34:31 by gsaiago          ###   ########.fr       */
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
	create_control(control, argv);
	pid = create_children(control);
	if (pid == 0)
	{
		vulture_create(control);
		dine(control);
	}
	sem_wait(control->death_sem);
	exit_func(control, 0);
	return (0);
}
