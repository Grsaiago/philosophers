/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:21:02 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/03 21:18:07 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>

typedef struct s_control
{
	int					nph;
	int					phid;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
	int					max_eat;
	int					times_eaten;
	int					*philov;
	sem_t				*forks;
	sem_t				*death_sem;
	sem_t				*stout_sem;
	pthread_t			vulture_thread;
	pthread_mutex_t		last_meal_access;
	pthread_mutex_t		times_eaten_access;
	long unsigned int	last_meal;
	long unsigned int	timestamp;
	struct timeval		tv_timestamp;
	struct timeval		tv_last_meal;

}	t_control;

/* VALIDATION */
int			validate_args(int ac, char **av);
int			ph_isdigit(int c);
int			if_in_range(int ac, char **av);
int			if_number(int ac, char **av);
/* AUX FUNCTIONS */
void		create_control(t_control *control, char **av, int times_eat);
void		*ph_calloc(int size, int bytes);
long int	get_time(struct timeval *tv, int i);
void		death_refresh(t_control *control);
int			create_children(t_control *control);
/* DINE FUNCTION */
void		dine(t_control *control);
void		dine_take_forks(t_control *control);
void		dine_eat(t_control *control);
void		add_meal(t_control *control);
/* VULTURE FUNC */
void		vulture_create(t_control *control);
void		*vulture_exec(void *ptr);
void		still_alive(t_control *control);
void		stop_eating(t_control *control);
/* ATOL */
long int	ft_atol(const char *str);
long int	ft_pow10(int n);
long int	ft_tatoi(const char *str, int sign);
/* EXIT FUNC */
void		exit_func(t_control *control);

#endif
