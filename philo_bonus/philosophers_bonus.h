/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:21:02 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/03 16:57:42 by gsaiago          ###   ########.fr       */
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
	int					*philov;
	sem_t				*forks;
	sem_t				*death_sem;
	sem_t				*stout_sem;
	pthread_t			vulture_thread;
	pthread_mutex_t		last_meal_access;
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
void 		create_control(t_control *control, char **av);
void		*ph_calloc(int size, int bytes);
long int	get_time(struct timeval *tv, int i);
void		death_refresh(t_control *control);
/* VULTURE FUNC */
void		vulture_create(t_control *control);
void		*vulture_exec(void *ptr);
/* ATOL */
long int	ft_atol(const char *str);
long int	ft_pow10(int n);
long int	ft_tatoi(const char *str, int sign);
//void		thread_execute(t_control *control); // vai chamar a vulture, vai ser a função passada no thread_create
//void		vulture(void *ptr); //essa vai ser a função que fica vendo se o philo tem que morrer
//void		allow_death(t_control *control); // vai dar free em memória alocada pelos child e incrementar um semáforo de matar geral, que vai estar em sem_wait na main;
//void		kill_process(t_control *control); // vai dar free em memória alocada na heap e incrementar o semáforo de matar geral na main;

#endif
