/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:56:21 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/16 13:52:22 by gsaiago          ###   ########.fr       */
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
	int					nph;
	int					phid;
	int					prev_f;
	int					next_f;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat;
	int					times_eaten;
	int					*fork_state;
	pthread_mutex_t		*fork_state_access;
	int					*stop_eating;
	pthread_mutex_t		*stop_eating_access;
	long unsigned int	*last_meal;
	pthread_mutex_t		*last_meal_access;
	pthread_mutex_t		*forkv;
	char				*philo_state;
	pthread_mutex_t		*philo_state_access;
	struct timeval		tv;
}	t_philo;

typedef struct s_control
{
	int					nph;
	int					time_to_die;
	int					max_eat;
	pthread_t			*thv;
	t_philo				**philov;
	int					*fork_state;
	pthread_mutex_t		*fork_state_access;
	long unsigned int	*last_meal;
	pthread_mutex_t		*last_meal_access;
	int					*stop_eating;
	pthread_mutex_t		*stop_eating_access;
	pthread_mutex_t		*forkv;
	char				*philo_state;
	pthread_mutex_t		*philo_state_access;
	pthread_mutex_t		*vulture_return_access;
	char				*vulture_return;
	pthread_t			vulture;
	struct timeval		tv;
}	t_control;

/* AUX FUNCTIONS */
void		*ph_calloc(int size, int bytes);
long int	get_time(struct timeval *tv, int i);
long int	ft_atol(const char *str);
long int	ft_tatoi(const char *str, int sign);
long int	ft_pow10(int n);
/* VALIDATION */
int			validate_args(int ac, char **av);
int			ph_isdigit(int c);
int			if_in_range(int ac, char **av);
int			if_number(int ac, char **av);
/* THREAD CREATION & EXECUTION */
void		initialize_mutex_struct_thread(t_control *control, char **av);
void		create_control(t_control *control, char **av, int if_times_eat);
t_philo		*create_thread_struct(t_control *control, int i, char **av);
void		*dine(void *ptr);
int			ph_think(t_philo *philo);
int			ph_eat(t_philo *philo);
int			ph_sleep(t_philo *philo);
int			take_forks(t_philo *philo);
void		return_forks(t_philo *philo);
int			add_meal(t_philo *philo);
void		death_refresh(t_philo *philo);
int			stop_execution(t_philo	*philo);
int			trylock_fork(t_philo *philo, int n_fork);
void		ph_unlock_fork(t_philo *philo, int n_fork);
int			last_philo_fork_take(t_philo *philo);
int			other_philo_fork_take(t_philo *philo);
/* VULTURE */
void		*vulture(void *ptr);
int			stop_eating(t_control *control);
int			check_philo_death(t_control *control, int i);
int			check_vulture_return(t_control *control);
/* EXIT FUNCTIONS */
void		free_all(t_control *control);
void		kill_vulture(t_control *control);
void		kill_mutexes(t_control	*control);
void		exit_func(t_control *control);

#endif
