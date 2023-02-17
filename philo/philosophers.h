/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:56:21 by gsaiago           #+#    #+#             */
/*   Updated: 2023/02/17 12:43:24 by gsaiago          ###   ########.fr       */
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
# include <stdint.h>

typedef struct s_philo
{
	uint8_t				nph;
	uint8_t				phid;
	uint8_t				phindex;
	uint8_t				is_even;
	uint8_t				prev_f;
	uint8_t				next_f;
	int					max_eat;
	int					time_to_eat;
	int					time_to_sleep;
	int					*times_eaten;
	pthread_mutex_t		*times_eaten_access;
	int					*fork_state;
	pthread_mutex_t		*fork_state_access;
	long unsigned int	*last_meal;
	pthread_mutex_t		*last_meal_access;
	int					*stop_eating;
	pthread_mutex_t		*stop_eating_access;
}	t_philo;

typedef struct s_control
{
	uint8_t				nph;
	long unsigned int 	time_to_die;
	int					max_eat;
	pthread_t			*thv;
	t_philo				**philov;
	int					*times_eaten;
	pthread_mutex_t		*times_eaten_access;
	int					*fork_state;
	pthread_mutex_t		*fork_state_access;
	long unsigned int	*last_meal;
	pthread_mutex_t		*last_meal_access;
	int					*stop_eating;
	pthread_mutex_t		*stop_eating_access;
	pthread_t			vulture;
}	t_control;

/* AUX FUNCTIONS */
void		*ph_calloc(int size, int bytes);
long int	get_time(int i);
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
int			smart_sleep(t_philo *philo, long unsigned int usec);
int			trylock_fork(t_philo *philo, int n_fork);
void		ph_unlock_fork(t_philo *philo, int n_fork);
int			even_philo_fork_take(t_philo *philo);
int			odd_philo_fork_take(t_philo *philo);
/* VULTURE */
void		*vulture(void *ptr);
int			stop_eating(t_control *control);
int			check_eaten_times(t_control *control);
int			check_philo_death(t_control *control, int i);
/* EXIT FUNCTIONS */
void		free_all(t_control *control);
void		kill_mutexes(t_control	*control);
void		exit_func(t_control *control);

#endif
