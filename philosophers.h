/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:56:21 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/19 17:31:32 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	int						nph;
	int						phid;
	int						prev_f;
	int						next_f;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	long unsigned int		*mementomori;
	struct timeval			tv;
	pthread_mutex_t			*forkv;
}	t_philo;

typedef struct s_control
{
	int							nph;
	int							time_to_die;
	long unsigned int			*mementomori;
	pthread_mutex_t				*forkv;
	pthread_t					*thv;
	pthread_t					vulture;
	t_philo						**philov;
	struct timeval				tv;
}	t_control;

void	*ph_calloc(int size, int bytes);
void	death_refresh(t_philo *philo);
void	*vulture(void *ptr);
// EXIT FUNCTIONS //
void	free_all(t_control *control);
void	kill_threads(t_control	*control);

#endif
