/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:56:21 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/14 19:47:09 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_philo
{
	int	phid;
	int	forks;
	int	prev_f;
	int	next_f;
}	t_philo;

typedef struct s_control
{
	int			forks;
	int			nph;
	int			*phidv;
	pthread_t	*thv;
	t_philo		**philov;
}	t_control;

#endif

