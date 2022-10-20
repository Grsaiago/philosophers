/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_vulture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:38:57 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/20 19:49:38 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*vulture(void *ptr)
{
	long int	current_time;
	long int	diff;
	int			i;
	t_control	*control;

	control = (t_control *)ptr;
	i = 0;
	while (42)
	{
		if (i == control->nph)
			i = 0;
//		printf("control->last_meal[%d]> |%ld|\n", i, control->last_meal[i]);
//		printf("current_time> |%ld|\n", current_time);
//		printf("control->time_to_die> |%d|\n", control->time_to_die);
//		printf("current_time - control->last_meal[%d]> |%ld|\n", i, current_time - control->last_meal[i]);
		pthread_mutex_lock(&control->death_access[i]);
		current_time = get_time(&control->tv);
		diff = current_time - control->last_meal[i];
		if (diff > control->time_to_die && (control->last_meal[i] != 0))
			break ;
		pthread_mutex_unlock(&control->death_access[i]);
		i++;
	}
	current_time = get_time(&control->tv);
	printf("%d has died\n", i + 1);
	exit_func(control);
	return (NULL);
}
