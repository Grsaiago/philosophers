/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:56:21 by gsaiago           #+#    #+#             */
/*   Updated: 2022/10/20 16:15:16 by gsaiago          ###   ########.fr       */
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
	int						time_to_eat;
	int						time_to_sleep;
	long unsigned int		*last_meal;
	pthread_mutex_t			*death_access;
	pthread_mutex_t			*forkv;
	struct timeval			tv;
}	t_philo;

typedef struct s_control
{
	int							nph;
	int							time_to_die;
	long unsigned int			*last_meal;
	pthread_t					vulture;
	pthread_mutex_t				*forkv;
	pthread_mutex_t				*death_access;
	pthread_t					*thv;
	t_philo						**philov;
	struct timeval				tv;
}	t_control;
// AUX FUNCTIONS //
void	*ph_calloc(int size, int bytes);
// THREAD CREATION & EXECUTION //
t_philo	*create_thread_struct(t_control *control, int i, char **av);
void	dine(t_philo *philo);
// VULTURE //
void	death_refresh(t_philo *philo);
void	*vulture(void *ptr);
// EXIT FUNCTIONS //
void	free_all(t_control *control);
void	kill_threads(t_control	*control);
void	create_control(t_control *control, char **av);
void	validate_args(int ac, char **av);

#endif
